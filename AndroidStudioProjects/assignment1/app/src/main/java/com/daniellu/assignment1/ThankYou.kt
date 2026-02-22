package com.daniellu.assignment1

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import org.w3c.dom.Text

class ThankYou : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_thank_you)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
        val thankYouMSG : TextView = findViewById(R.id.tvThankYou)

        thankYouMSG.text = "Thanks for Registration, ${intent.getStringExtra("key_fName")}"

        val lastName : TextView = findViewById(R.id.tvLastName)
        lastName.text = intent.getStringExtra("key_lName")

        val email : TextView = findViewById(R.id.tvEmail)
        email.text = intent.getStringExtra("key_email")

        val gender : TextView = findViewById(R.id.tvGenderSelection)
        gender.text = intent.getStringExtra("key_gender")

        val termsConditions : TextView = findViewById(R.id.tvAgreementStatus)
        termsConditions.text = intent.getStringExtra("key_termsAgreement")

        val btnReturnReg : Button = findViewById(R.id.btnReturnReg)

        btnReturnReg.setOnClickListener {
            val registrationIntent = Intent (
                applicationContext,
                Registration::class.java
            )

            startActivity(registrationIntent)
        }

    }
}