package com.example.roomdbdemo

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.room.Room
import java.util.concurrent.Executors

class MainActivity : AppCompatActivity() {

    private lateinit var database: AppDatabase

    private lateinit var tvOutput : TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        tvOutput = findViewById(R.id.tvOutput)

        val etFirstName : EditText = findViewById(R.id.etFirstName)
        val etLastName : EditText = findViewById(R.id.etLastName)
        val etEmail : EditText = findViewById(R.id.etEmail)

        val btnInsert : Button = findViewById(R.id.btnInsert)
        val btnRetrieve : Button = findViewById(R.id.btnRetrieve)
        val btnDelete : Button = findViewById(R.id.btnDelete)

        database = Room.databaseBuilder(
            applicationContext,
            AppDatabase::class.java, "user-database-name"
        ).build()

        btnInsert.setOnClickListener {
            insertUsers(
                etFirstName.text.toString().trim(),
                etLastName.text.toString().trim(),
                etEmail.text.toString().trim()
            )
        }

        btnRetrieve.setOnClickListener {
            retrieveUsers()
        }

        btnDelete.setOnClickListener {
            deleteUser()
        }

//        insertUsers("Jenny", "Fong", "jennyfong@gmail.com")
//        database.userDao().insertUser(
//            User(
//                firstName = "John",
//                lastName = "Doe",
//                email = "johndoe@gmail.com"
//            )
//        )
    }

    private fun insertUsers( fName : String, lName: String, email : String){
        val user = User(firstName = fName, lastName = lName, email = email)
        Executors.newSingleThreadExecutor().execute {
            database.userDao().insertUser(user)
            retrieveUsers()
        }
    }

    private fun retrieveUsers(){
        Executors.newSingleThreadExecutor().execute {
            val usersRecd = database.userDao().getAllUsers()

            runOnUiThread {
                tvOutput.text = usersRecd.joinToString("\n"){
                    "${it.uid} - ${it.firstName} - ${it.lastName} - ${it.email}"
                }
            }

        }
    }

    private fun deleteUser(){
        Executors.newSingleThreadExecutor().execute {
            val usersRecd = database.userDao().getAllUsers()
            database.userDao().deleteUser(usersRecd[usersRecd.size - 1])
            retrieveUsers()
        }
    }
}