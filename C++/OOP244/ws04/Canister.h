#ifndef SENECA_CANISTER_H
#define SENECA_CANISTER_H
#include <iostream>
namespace seneca {
    class Canister {
        char* m_contentName; // points to a dynamically allocated Cstring.
        double m_diameter; // in centimeters 
        double m_height;   // in centimeters
        double m_contentVolume;  // in CCs

        /// <summary>
        /// renders the canister unusable by freeing the conent name memory and setting diamieter and height to -1
        /// </summary>
        void setToUnusable();
        /// <summary>
        /// Returns true if canister volume is below 0.00001
        /// </summary>
        /// <returns>true if the canister is emtpy</returns>
        bool isEmpty()const;
        /// <summary>
        /// Returns true if height and diameters are within accepable values
        /// </summary>
        /// <returns>true if canister is usable</returns>
        bool usable()const;
        /// <summary>
        /// Returns true if the conent name of the two canisters are the same
        /// </summary>
        /// <param name="C">const Canister& to compare to</param>
        /// <returns>True if the name is the same</returns>
        bool hasSameContent(const Canister& C)const;
        /// <summary>
        /// returns the capacity of the canister
        /// </summary>
        /// <returns>Capacity of Canister</returns>
        double capacity()const;
        /// <summary>
        /// Returns the content volume. Always less than capacity
        /// </summary>
        /// <returns>Conent Volume</returns>
        double volume()const;
    public:

        /// <summary>
        /// Sets the object to default values when no parameters are set
        /// </summary>
        Canister();

        /// <summary>
        /// Takes the contentName parameter and sets it as the objects contentName
        /// All other values are default
        /// </summary>
        Canister(const char* contentName);

        /// <summary>
        /// Takes the parameters and sets its corresponding values to the objects attributes
        /// </summary>
        Canister(double height, double diameter, const char* contentName = nullptr);

        /// <summary>
        /// Destructs the selected object
        /// </summary>
        ~Canister();

        /// <summary>
        /// Deallocating the memory pointed to by the content name attribute (use the freemem function)
        /// Setting the content volume attribute to 0.0
        /// </summary>
        /// <return> Reference to the current Canister object </return>
        Canister& clear();

        /// <summary>
        /// 
        /// </summary>
        /// <return>  </return>
        Canister& setContent(const char* contentName);

        /// <summary>
        /// 
        /// </summary>
        /// <return>  </return>
        Canister& pour(double quantity);

        /// <summary>
        /// 
        /// </summary>
        /// <return>  </return>
        Canister& pour(Canister& can);

        std::ostream& display()const;

    };
}

#endif // !SENECA_BOX_H
