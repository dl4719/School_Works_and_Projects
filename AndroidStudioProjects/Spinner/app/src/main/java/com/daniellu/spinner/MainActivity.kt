package com.daniellu.spinner

import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.Spinner
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val spinnerCountries : Spinner = findViewById(R.id.spinnerCountries)

        val btnSpinner : Button = findViewById(R.id.btnSpinner)

        val countries = listOf("Canada", "United Kingdom", "New Zealand", "Australia", "USA")

        val adapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_item,
            countries
        )
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_item)

        spinnerCountries.adapter = adapter

        ////////////////////
        btnSpinner.setOnClickListener {
            Toast.makeText(
                applicationContext,
                "The selected country at form submission is ${spinnerCountries.selectedItem}",
                Toast.LENGTH_SHORT
            ).show()
        }
        ////////////////////
        // Two different ways to verify values
        ////////////////////
        spinnerCountries.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(
                parent: AdapterView<*>?,
                view: View?,
                position: Int,
                id: Long
            ) {
                Toast.makeText(
                    applicationContext,
                    "The selected country is ${countries[position]}",
                    Toast.LENGTH_SHORT
                ).show()
            }

            override fun onNothingSelected(parent: AdapterView<*>?) {
                TODO("Not yet implemented")
            }
        }
        ////////////////////

        
    }
}