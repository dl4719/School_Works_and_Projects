package com.example.assignment3

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.room.Room
import java.util.concurrent.Executors

private lateinit var database: AppUserDatabase
private lateinit var rvDisplayAllUsers : RecyclerView

class DisplayAllUsers : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_display_all_users)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val btnBackToNewUser : Button = findViewById(R.id.btnBackToNewUser)

        rvDisplayAllUsers = findViewById(R.id.rvDisplayAllUsers)
        rvDisplayAllUsers.layoutManager = LinearLayoutManager(this)

        database = Room.databaseBuilder(
            applicationContext,
            AppUserDatabase::class.java,
            "user-database"
        ).fallbackToDestructiveMigration().build()

        loadUsersFromDatabase()

        btnBackToNewUser.setOnClickListener{
            val mainActivityIntent = Intent(
                applicationContext,
                MainActivity::class.java
            )
            startActivity(mainActivityIntent)
        }
    }

    private fun loadUsersFromDatabase() {
        Executors.newSingleThreadExecutor().execute {
            val userList = database.userDao().getAllUsers()

            runOnUiThread {
                val loadUsersAdapter = UserAdapter(this@DisplayAllUsers, userList)
                rvDisplayAllUsers.adapter = loadUsersAdapter
            }
        }
    }

    override fun onResume() {
        super.onResume()
        loadUsersFromDatabase()
    }
}