package com.example.assignment3

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.room.Room
import java.util.concurrent.Executors


class MainActivity : AppCompatActivity() {

    private lateinit var database: AppUserDatabase

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val etFName : EditText = findViewById(R.id.etFName)
        val etLName : EditText = findViewById(R.id.etLName)
        val etEmail : EditText = findViewById(R.id.etEmail)

        val btnSaveData : Button = findViewById(R.id.btnSaveData)
        val btnDetailsActivity : Button = findViewById(R.id.btnDetailsActivity)

        database = Room.databaseBuilder(
            applicationContext,
            AppUserDatabase::class.java,
            "user-database"
        ).fallbackToDestructiveMigration().build()

        btnSaveData.setOnClickListener {
            insertUser(
                etFName.text.toString().trim(),
                etLName.text.toString().trim(),
                etEmail.text.toString().trim()
            )
        }

        btnDetailsActivity.setOnClickListener {
            val displayUsersIntent = Intent(
                applicationContext,
                DisplayAllUsers::class.java
            )

            var fName : String = etFName.text.toString().trim()
            var lName : String = etLName.text.toString().trim()

            var email : String = etEmail.text.toString().trim()

            displayUsersIntent.putExtra("key_fName", fName)
            displayUsersIntent.putExtra("key_lName", lName)
            displayUsersIntent.putExtra("key_email", email)

            startActivity(displayUsersIntent)
        }
    }

    private fun insertUser(fName: String, lName: String, email: String){
        val newUser = User(firstName = fName, lastName = lName, email = email)
        Executors.newSingleThreadExecutor().execute {
            database.userDao().insertUser(newUser)

            runOnUiThread {
                Toast.makeText(
                    this,
                    "User saved successfully!",
                    Toast.LENGTH_SHORT
                ).show()
            }
        }
    }
}