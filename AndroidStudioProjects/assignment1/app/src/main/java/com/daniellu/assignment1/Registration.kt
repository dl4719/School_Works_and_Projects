package com.daniellu.assignment1

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.CheckBox
import android.widget.EditText
import android.widget.RadioButton
import android.widget.RadioGroup
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class Registration : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_registration)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val etFirstName : EditText = findViewById(R.id.etFirstName)
        val etLastName : EditText = findViewById(R.id.etLastName)
        val etEmail : EditText = findViewById(R.id.etEmail)

        val rgGender : RadioGroup = findViewById(R.id.rgGender)
        val rbMale : RadioButton = findViewById(R.id.rbMale)
        val rbFemale : RadioButton = findViewById(R.id.rbFemale)
        val rbOther : RadioButton = findViewById(R.id.rbOther)

        val cbAgree : CheckBox = findViewById(R.id.cbTerms_Conditions)

        val btnRegister : Button = findViewById(R.id.btnRegister)

        btnRegister.setOnClickListener {
            val thankYouIntent = Intent (
                applicationContext,
                ThankYou::class.java
            )
            val rgGenderSelection : RadioButton = findViewById(rgGender.checkedRadioButtonId)

            var fName : String = etFirstName.text.toString().trim()
            var lName : String = etLastName.text.toString().trim()
            var email : String = etEmail.text.toString().trim()

            var gender : String = rgGenderSelection.text.toString().trim()
            var checkBoxIsChecked : String = cbAgree.isChecked.toString().trim()

            thankYouIntent.putExtra("key_fName", fName)
            thankYouIntent.putExtra("key_lName", lName)
            thankYouIntent.putExtra("key_email", email)
            thankYouIntent.putExtra("key_gender", gender)
            thankYouIntent.putExtra("key_termsAgreement", checkBoxIsChecked)

            startActivity(thankYouIntent)
        }

    }
}