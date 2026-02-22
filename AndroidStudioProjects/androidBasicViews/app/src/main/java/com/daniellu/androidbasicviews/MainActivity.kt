package com.daniellu.androidbasicviews

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import android.widget.TextView
import android.content.Intent

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

        val tvOutput : TextView = findViewById(R.id.tvOutput)

        val etFirstName : EditText = findViewById(R.id.etFirstName)
        val etLastName : EditText = findViewById(R.id.etLastName)
        val email : EditText = findViewById(R.id.etEmail)

        val btnRegister : Button = findViewById(R.id.btnRegister)

        btnRegister.setOnClickListener {
            var fName : String = etFirstName.text.toString().trim()
            var lName : String = etLastName.text.toString().trim()

            tvOutput.text = "$fName \n $lName \n ${email.text.toString().trim()}"

            val activityTwoIntent : Intent = Intent(applicationContext, MainActivity2::class.java)
            activityTwoIntent.putExtra("key_fName", fName)
            startActivity(activityTwoIntent)

            /*Toast.makeText(applicationContext,
                fName,
                Toast.LENGTH_SHORT
            ).show()*/
        }
    }
}