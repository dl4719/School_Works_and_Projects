# Feel free to add additional python files to this project and import
# them in this file. However, do not change the name of this file
# Avoid the names ms1check.py and ms2check.py as those file names
# are reserved for the autograder

# To run your project use:
#     python runproject.py

# This will ensure that your project runs the way it will run in the
# the test environment

import re
import csv
import os
from datetime import datetime
import ast

# This function reads a csv file and return a list of lists
# each element of the returned list is a row in the csv file
# The first row is the header row
def read_csv_file(file_name):
    data_set = []
    with open(file_name, mode='r', encoding="utf-8-sig") as file:
        csv_reader = csv.reader(file)
        for row in csv_reader:
            data_set.append(row)
    return data_set

# This function writes out a list of lists to a csv file
# each element of the list is a row in the csv file
# The first row is the header row
def write_csv_file(file_name, data_set):
    with open(file_name, mode='w', newline='', encoding="utf-8-sig") as file:
        csv_writer = csv.writer(file)
        for row in data_set:
            csv_writer.writerow(row)

# --- Date Cleaning Function - Enhanced ---
def clean_date_format(date_str):
    """
    Converts various date formats to dd-Mon-yyyy format.
    Assumes all 2-digit years are in the 1900s.
    Returns empty string for invalid/missing dates.
    """
    if not date_str or date_str.strip() == '':
        return ''
    
    date_str = date_str.strip()
    
    # Fix two-digit year manually before parsing
    # Matches dd-Mmm-yy or dd Mmm yy (e.g., "04-Apr-49")
    match = re.match(r'(\d{1,2}[-\s][A-Za-z]{3}[-\s])(\d{2})$', date_str)
    if match:
        prefix = match.group(1)
        two_digit_year = int(match.group(2))
        full_year = 1900 + two_digit_year
        date_str = f"{prefix}{full_year}"
    
    # If only year present (4 digits)
    if date_str.isdigit() and len(date_str) == 4:
        return f"01-Jan-{date_str}"
    
    # Try various date formats
    formats = [
        "%d-%b-%Y", "%d %b %Y", "%d %B %Y", "%Y-%m-%d",
        "%d/%m/%Y", "%m/%d/%Y", "%Y/%m/%d", "%d.%m.%Y"
    ]
    
    for fmt in formats:
        try:
            dt = datetime.strptime(date_str, fmt)
            return dt.strftime("%d-%b-%Y")
        except ValueError:
            continue
    
    return date_str  # Return empty string for unparseable dates


# --- Clean Olympic Games CSV ---
def clean_olympics_games_data(original_path, output_path):
    data = read_csv_file(original_path)
    header = data[0]

    col_index = {col.lower(): i for i, col in enumerate(header)}

    start_date_idx = col_index.get("start_date")
    end_date_idx = col_index.get("end_date")
    competition_date_idx = col_index.get("competition_date")

    cleaned_data = [header]

    def normalize_space(s):
        # Remove leading/trailing whitespace and collapse multiple spaces inside to 1 space
        if not isinstance(s, str):
            return ''
        s = s.strip()
        s = re.sub(r'\s+', ' ', s)
        return s

    for row in data[1:]:
        while len(row) < len(header):
            row.append('')

        # Normalize all fields
        row = [normalize_space(f) for f in row]

        cleaned_row = row[:]

        # Clean date fields explicitly with stripping again (safe)
        if start_date_idx is not None:
            cleaned_row[start_date_idx] = clean_date_format(cleaned_row[start_date_idx].strip())

        if end_date_idx is not None:
            cleaned_row[end_date_idx] = clean_date_format(cleaned_row[end_date_idx].strip())

        if competition_date_idx is not None:
            comp_date = cleaned_row[competition_date_idx].strip()
            if comp_date and (' to ' in comp_date or '–' in comp_date or '-' in comp_date):
                # Normalize various dash types as " to "
                comp_date_fixed = comp_date.replace('–', ' to ').replace('-', ' to ')
                parts = [p.strip() for p in comp_date_fixed.split(' to ')]
                if len(parts) == 2:
                    start_clean = clean_date_format(parts[0])
                    end_clean = clean_date_format(parts[1])
                    if start_clean and end_clean:
                        cleaned_row[competition_date_idx] = f"{start_clean} to {end_clean}"
                    else:
                        cleaned_row[competition_date_idx] = 'N/A'
                else:
                    cleaned_row[competition_date_idx] = clean_date_format(comp_date)
            elif comp_date:
                cleaned_row[competition_date_idx] = clean_date_format(comp_date)
            else:
                cleaned_row[competition_date_idx] = 'N/A'

        # Fill empty fields with default values
        if start_date_idx is not None and (cleaned_row[start_date_idx] == "" or cleaned_row[start_date_idx].upper() == "N/A"):
                if ' to ' in cleaned_row[competition_date_idx]:
                    cleaned_row[start_date_idx] = cleaned_row[competition_date_idx].split(' to ')[0]
                else:
                    cleaned_row[start_date_idx] = cleaned_row[competition_date_idx]

        # If end_date is empty, use last date from competition_date
        if end_date_idx is not None and (cleaned_row[end_date_idx] == "" or cleaned_row[end_date_idx].upper() == "N/A"):
            if ' to ' in cleaned_row[competition_date_idx]:
                cleaned_row[end_date_idx] = cleaned_row[competition_date_idx].split(' to ')[-1]
            else:
                cleaned_row[end_date_idx] = cleaned_row[competition_date_idx]

        cleaned_data.append(cleaned_row)
    write_csv_file(output_path, cleaned_data)

# --- Clean Athlete Bio Data ---
def clean_athlete_bio_data(original_path, output_path):
    """
    Clean the athlete bio data by:
    - Standardizing 'born' date format
    - Filling missing values with defaults
    """

    default_vals = {
        "athlete_id": "N/A",
        "name": "Unknown",
        "sex": "Unknown",
        "born": "Unknown",
        "height": "0",
        "weight": "0",
        "country": "Unknown",
        "country_noc": "XXX"
    }
    
    data = read_csv_file(original_path)
    header = data[0]

    # Find the 'born' column index
    born_idx = None
    for i, col in enumerate(header):
        if col.lower() == 'born':
            born_idx = i
            break

    cleaned_data = [header]

    for row in data[1:]:
        # Ensure row has enough columns
        while len(row) < len(header):
            row.append('')

        cleaned_row = row[:]

        # # Clean the born date field
        if born_idx is not None and born_idx < len(row):
            cleaned_row[born_idx] = clean_date_format(row[born_idx])

        # Fill empty fields with defaults
        for i, val in enumerate(cleaned_row):
            if val.strip() == "":
                col_name = header[i].lower()
                cleaned_row[i] = default_vals.get(col_name, "")

        cleaned_data.append(cleaned_row)

    write_csv_file(output_path, cleaned_data)


# --- Add Paris Athletes to Bio Data ---
def add_paris_athletes_to_bio(bio_path, paris_athletes_path, output_path):
    """
    Clean Paris 2024 athlete data, fill defaults, and add to bio data without duplicates.
    """

    paris_default_vals = {
        "code": "N/A",
        "current": "False",
        "name": "Unknown",
        "name_short": "Unknown",
        "name_tv": "Unknown",
        "gender": "Unknown",
        "function": "Unknown",
        "country_code": "XXX",
        "country": "Unknown",
        "country_long": "Unknown",
        "nationality": "Unknown",
        "nationality_long": "Unknown",
        "nationality_code": "XXX",
        "height": "0",
        "weight": "0",
        "disciplines": "Unknown",
        "events": "Unknown",
        "birth_date": "Unknown",
        "birth_place": "Unknown",
        "birth_country": "Unknown",
        "residence_place": "Unknown",
        "residence_country": "Unknown"
}
    # Read existing bio data
    bio_data = read_csv_file(bio_path)
    bio_header = bio_data[0]

    # Read Paris athletes data
    if not os.path.exists(paris_athletes_path):
        print(f"Paris athletes file not found: {paris_athletes_path}")
        write_csv_file(output_path, bio_data)
        return

    paris_data = read_csv_file(paris_athletes_path)
    if len(paris_data) < 2:
        print("Paris athletes file is empty or has no data rows")
        write_csv_file(output_path, bio_data)
        return

    paris_header = paris_data[0]
    paris_col_index = {col.lower(): i for i, col in enumerate(paris_header)}

    # Clean Paris data first
    cleaned_paris_data = [paris_header]
    birth_date_idx = paris_col_index.get("birth_date")

    for row in paris_data[1:]:
        while len(row) < len(paris_header):
            row.append('')
        cleaned_row = row[:]

        # Clean birth_date
        if birth_date_idx is not None:
            cleaned_row[birth_date_idx] = clean_date_format(row[birth_date_idx])

        # Fill defaults
        for i, val in enumerate(cleaned_row):
            if val.strip() == "":
                col_name = paris_header[i].lower()
                cleaned_row[i] = paris_default_vals.get(col_name, "")

        cleaned_paris_data.append(cleaned_row)

    # Overwrite Paris CSV with cleaned version (optional)
    cleaned_paris_path = os.path.join(os.path.dirname(paris_athletes_path), "paris_athletes_cleaned.csv")
    write_csv_file(cleaned_paris_path, cleaned_paris_data)

    # Map existing athletes to avoid duplicates
    existing_athletes = {row[0].strip().lower() for row in bio_data[1:] if row and row[0].strip()}

    # Find athlete_id column in bio
    max_id = 0
    athlete_id_idx = None
    for i, col in enumerate(bio_header):
        if 'athlete_id' in col.lower() or 'id' in col.lower():
            athlete_id_idx = i
            break

    if athlete_id_idx is not None:
        for row in bio_data[1:]:
            if len(row) > athlete_id_idx and row[athlete_id_idx].isdigit():
                max_id = max(max_id, int(row[athlete_id_idx]))

    # Add cleaned Paris athletes to bio
    new_bio_data = bio_data[:]
    for paris_row in cleaned_paris_data[1:]:
        athlete_name = paris_row[paris_col_index["name"]].strip().lower()
        if athlete_name and athlete_name not in existing_athletes:
            max_id += 1
            new_row = [''] * len(bio_header)

            # Set athlete_id
            if athlete_id_idx is not None:
                new_row[athlete_id_idx] = str(max_id)

            # Map basic fields from Paris data to bio data
            for i, col in enumerate(bio_header):
                col_lower = col.lower()
                if col_lower in paris_col_index:
                    new_row[i] = paris_row[paris_col_index[col_lower]]

            new_bio_data.append(new_row)
            existing_athletes.add(athlete_name)

    write_csv_file(output_path, new_bio_data)

# --- Calculate Age ---
def calculate_age(birth_date_str, olympics_year):
    """
    Calculate age based on birth date (full or partial) and Olympics year.
    Supports:
    - dd-Mon-YYYY
    - Mon-YYYY or Month YYYY
    - YYYY only
    Assumes all dates in 1900s unless year >= 2000.
    """
    if not birth_date_str or birth_date_str.strip().lower() in {'n/a', 'unknown'}:
        return ''
    
    birth_date_str = birth_date_str.strip()
    
    # Try multiple formats
    date_formats = [
        "%d-%b-%Y", "%d %B %Y",
        "%b-%Y", "%B %Y",
        "%Y"
    ]
    
    birth_date = None
    for fmt in date_formats:
        try:
            parsed = datetime.strptime(birth_date_str, fmt)
            # Fill missing components with defaults
            if fmt == "%Y":
                parsed = parsed.replace(month=1, day=1)
            elif fmt in ("%b-%Y", "%B %Y"):
                parsed = parsed.replace(day=1)
            birth_date = parsed
            break
        except ValueError:
            continue
    
    if not birth_date:
        return ''  # Unparseable date
    
    # Assume all 2-digit years in 1900s (just in case)
    if birth_date.year < 100:
        birth_date = birth_date.replace(year=1900 + birth_date.year)
    
    # Calculate approximate age (July 1 as Olympics date)
    olympics_date = datetime(olympics_year, 7, 1)
    age = olympics_date.year - birth_date.year
    if olympics_date.month < birth_date.month or \
       (olympics_date.month == birth_date.month and olympics_date.day < birth_date.day):
        age -= 1
    
    return str(age) if age >= 0 else ''

# --- Add Ages to Event Results ---
def add_ages_to_event_results(bio_path, events_path, games_path, output_path):
    """
    Create a cleaned copy of olympic_athlete_event_results.csv with an added 'age' column.
    The age is calculated from athlete birth dates (bio file) and Olympic year (games file).
    Also replaces empty fields with default values.
    """
    # Read data
    bio_data = read_csv_file(bio_path)
    events_data = read_csv_file(events_path)
    games_data = read_csv_file(games_path)
    
    if len(events_data) == 0:
        return
    
    events_header = events_data[0]

    # Default values for events file
    event_defaults = {
        "edition": "Unknown Edition",
        "edition_id": "0",
        "country_noc": "XXX",
        "sport": "Unknown Sport",
        "event": "Unknown Event",
        "result_id": "0",
        "athlete": "Unknown Athlete",
        "athlete_id": "N/A",
        "pos": "0",
        "medal": "None",
        "isTeamSport": "False"
    }
    
    # Replace empty values in events_data with defaults
    for row in events_data[1:]:
        for col_idx, col_name in enumerate(events_header):
            default_value = event_defaults.get(col_name.strip(), "")
            if col_idx < len(row):
                if not row[col_idx] or row[col_idx].strip() == "":
                    row[col_idx] = default_value
            else:
                # Add missing columns as defaults
                row.append(default_value)
    
    # Add age column if not present
    if 'age' not in [col.lower() for col in events_header]:
        events_header.append('age')
    
    # Create athlete birth date lookup
    athlete_birth_dates = {}
    bio_header = bio_data[0] if len(bio_data) > 0 else []
    
    athlete_id_idx = None
    born_idx = None
    
    for i, col in enumerate(bio_header):
        col_lower = col.strip().lower()
        if col_lower == 'athlete_id':
            athlete_id_idx = i
        elif col_lower == 'born':
            born_idx = i
    
    if athlete_id_idx is not None and born_idx is not None:
        for row in bio_data[1:]:
            if len(row) > max(athlete_id_idx, born_idx):
                athlete_id = row[athlete_id_idx].strip().lower()
                birth_date = row[born_idx].strip()
                athlete_birth_dates[athlete_id] = birth_date
    
    # Create games year lookup
    games_years = {}
    games_header = games_data[0] if len(games_data) > 0 else []

    edition_idx = None
    year_idx = None

    for i, col in enumerate(games_header):
        col_lower = col.strip().lower()
        if col_lower == 'edition':
            edition_idx = i
        elif col_lower == 'year':
            year_idx = i

    if edition_idx is not None and year_idx is not None:
        for row in games_data[1:]:
            if len(row) > max(edition_idx, year_idx):
                edition = row[edition_idx].strip().lower()
                year_str = row[year_idx].strip()
                try:
                    year = int(year_str)
                except:
                    year = None
                
                if year:
                    games_years[edition] = year
    
    # Process event results
    new_events_data = [events_header]
    
    # Find relevant column indices
    athlete_id_events_idx = None
    edition_events_idx = None
    age_idx = len(events_header) - 1  # Age is the last column
    
    for i, col in enumerate(events_header):
        col_lower = col.strip().lower()
        if col_lower == 'athlete_id':
            athlete_id_events_idx = i
        elif col_lower == 'edition':
            edition_events_idx = i
    
    for row in events_data[1:]:
        # Ensure row has enough columns
        while len(row) < len(events_header):
            row.append('')
        
        new_row = row[:]
        
        age = ''
        if athlete_id_events_idx is not None and edition_events_idx is not None:
            athlete_id = row[athlete_id_events_idx].strip().lower()
            edition = row[edition_events_idx].strip().lower()

            birth_date = athlete_birth_dates.get(athlete_id, '')
            olympics_year = games_years.get(edition)

            if birth_date:
                birth_date_clean = clean_date_format(birth_date)
            else:
                birth_date_clean = ''

            if birth_date_clean and olympics_year:
                age = calculate_age(birth_date_clean, olympics_year)
            else:
                age = ''

        new_row[age_idx] = age
        new_events_data.append(new_row)
    
    write_csv_file(output_path, new_events_data)

# --- Create Medal Tally ---
def create_medal_tally(events_path, games_path, countries_path, output_path):
    """
    Create medal tally summary file.
    """
    # Read data
    events_data = read_csv_file(events_path)
    games_data = read_csv_file(games_path)
    countries_data = read_csv_file(countries_path)
    
    if len(events_data) == 0:
        header = ['edition', 'edition_id', 'Country', 'NOC', 'number_of_athletes', 
                 'gold_medal_count', 'silver_medal_count', 'bronze_medal_count', 'total_medals']
        write_csv_file(output_path, [header])
        return
    
    # Create country lookup
    country_lookup = {}
    if len(countries_data) > 0:
        countries_header = countries_data[0]
        noc_idx = None
        country_idx = None
        
        for i, col in enumerate(countries_header):
            if 'noc' in col.lower() or 'code' in col.lower():
                noc_idx = i
            elif 'country' in col.lower() or 'nation' in col.lower():
                country_idx = i
        
        if noc_idx is not None and country_idx is not None:
            for row in countries_data[1:]:
                if len(row) > max(noc_idx, country_idx):
                    noc = row[noc_idx].strip()
                    country = row[country_idx].strip()
                    if noc and country:
                        country_lookup[noc] = country
    
    # Process events data
    events_header = events_data[0]
    
    # Find relevant columns
    edition_idx = None
    country_noc_idx = None
    medal_idx = None
    athlete_id_idx = None
    
    for i, col in enumerate(events_header):
        col_lower = col.lower()
        if 'edition' in col_lower:
            edition_idx = i
        elif 'country_noc' in col_lower or 'noc' in col_lower:
            country_noc_idx = i
        elif 'medal' in col_lower:
            medal_idx = i
        elif 'athlete_id' in col_lower or 'id' in col_lower:
            athlete_id_idx = i
    
    # Aggregate data
    tally_data = {}  # Key: (edition, noc), Value: {athletes: set, gold: int, silver: int, bronze: int}
    
    medal_events_seen = set()

    for row in events_data[1:]:
        if edition_idx is None or country_noc_idx is None or medal_idx is None:
            continue
        if len(row) <= max(edition_idx, country_noc_idx, medal_idx):
            continue

        edition = row[edition_idx].strip()
        noc = row[country_noc_idx].strip()
        medal = row[medal_idx].strip()
        athlete_id = row[athlete_id_idx].strip() if athlete_id_idx is not None and len(row) > athlete_id_idx else ""
        event_id = row[3] if len(row) > 3 else ""  # Assuming column 3 = event name/id

        if not edition or not noc or not medal:
            continue

        key = (edition, noc)
        if key not in tally_data:
            tally_data[key] = {'athletes': set(), 'gold': 0, 'silver': 0, 'bronze': 0}

        if athlete_id:
            tally_data[key]['athletes'].add(athlete_id)

        medal_lower = medal.lower()
        if medal_lower in ("gold", "silver", "bronze"):
            event_key = (edition, noc, medal_lower, event_id)
            if event_key not in medal_events_seen:
                tally_data[key][medal_lower] += 1
                medal_events_seen.add(event_key)
    
    # Create edition_id lookup
    edition_id_to_name = {}
    edition_name_to_id = {}

    if len(games_data) > 0:
        games_header = games_data[0]
        edition_name_idx = None
        edition_id_idx = None
        
        # Find correct columns for edition name and edition id
        for i, col in enumerate(games_header):
            col_lower = col.lower()
            if col_lower == "edition":  # Exact match to 'edition'
                edition_name_idx = i
            elif col_lower == "edition_id":
                edition_id_idx = i
        
        # Make sure both columns were found
        if edition_name_idx is not None and edition_id_idx is not None:
            for row in games_data[1:]:
                if len(row) > max(edition_name_idx, edition_id_idx):
                    edition_name = row[edition_name_idx].strip()   # Should be '1896 Summer Olympics', not URL
                    edition_id = row[edition_id_idx].strip()
                    edition_id_to_name[edition_id] = edition_name
                    edition_name_to_id[edition_name] = edition_id
    
    # Generate output
    header = ['edition', 'edition_id', 'Country', 'NOC', 'number_of_athletes', 
             'gold_medal_count', 'silver_medal_count', 'bronze_medal_count', 'total_medals']
    
    result_data = [header]
    
    for (edition_key, noc), data in tally_data.items():
    # edition_key might be edition id or edition name, normalize:
        if edition_key.isdigit():
            edition_name = edition_id_to_name.get(edition_key, edition_key)
            edition_id = edition_key
        else:
            edition_name = edition_key
            edition_id = edition_name_to_id.get(edition_name, '')

        country = country_lookup.get(noc, noc)
        num_athletes = len(data['athletes'])
        gold = data['gold']
        silver = data['silver']
        bronze = data['bronze']
        total = gold + silver + bronze

        row = [edition_name, edition_id, country, noc, str(num_athletes),
            str(gold), str(silver), str(bronze), str(total)]
        result_data.append(row)

    
    # Sort by edition and country
    result_data[1:] = sorted(result_data[1:], key=lambda x: (x[0], x[2]))
    
    write_csv_file(output_path, result_data)

# Main function - Updated for Milestone 2
def main():
    print("Starting Milestone 2 Processing...")
    
    # Task 2: Clean the data  
    # Because cleaning before adding
    print("Task 2: Cleaning data...")
    clean_athlete_bio_data('olympic_athlete_bio.csv', 'new_olympic_athlete_bio.csv')
    clean_olympics_games_data('olympics_games.csv', 'new_olympics_games.csv')
    
    # Task 1: Add Paris data
    print("Task 1: Adding Paris data...")
    add_paris_athletes_to_bio('new_olympic_athlete_bio.csv', 'paris/athletes.csv', 'new_olympic_athlete_bio.csv')
    
    # Copy countries data (with potential Paris additions)
    countries_data = read_csv_file('olympics_country.csv')
    write_csv_file('new_olympics_country.csv', countries_data)
    
    # Task 3: Add information (ages and medal tally)
    print("Task 3: Adding ages and creating medal tally...")
    add_ages_to_event_results('new_olympic_athlete_bio.csv', 'olympic_athlete_event_results.csv', 
                             'new_olympics_games.csv', 'new_olympic_athlete_event_results.csv')
    
    create_medal_tally('new_olympic_athlete_event_results.csv', 'new_olympics_games.csv', 
                      'new_olympics_country.csv', 'new_medal_tally.csv')
    
    print("Milestone 2: All tasks completed!")

if __name__ == "__main__":
    main()
