package com.example.assignment3

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.room.Room
import java.util.concurrent.Executors

private lateinit var database: AppUserDatabase

class UserDetailsActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_user_details)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        database = Room.databaseBuilder(
            applicationContext,
            AppUserDatabase::class.java,
            "user-database"
        ).fallbackToDestructiveMigration().build()

        val userProfile : ImageView = findViewById(R.id.userProfileImageView)
        val uid : Int = intent.getIntExtra("key_uid", -1)
        val tvUserProfileName : TextView = findViewById(R.id.tvUserProfileName)
        val tvUserProfileEmail : TextView = findViewById(R.id.tvUserProfileEmail)

        val btnDeleteUserProfile : Button = findViewById(R.id.btnDeleteUserProfile)
        val btnUserListDisplay : Button = findViewById(R.id.btnUserListDisplay)

        tvUserProfileName.text =
            intent.getStringExtra(
                "key_fName") + " " + intent.getStringExtra("key_lName")

        tvUserProfileEmail.text = intent.getStringExtra("key_email")

        val profile = intent.getIntExtra("key_userProfile", R.drawable.ic_launcher_foreground)

        userProfile.setImageResource(profile)

        btnDeleteUserProfile.setOnClickListener{
            deleteUser(uid)
        }

        btnUserListDisplay.setOnClickListener{
            val displayAllUsersIntent = Intent(
                applicationContext,
                DisplayAllUsers::class.java
            )
            startActivity(displayAllUsersIntent)
        }
    }

    private fun deleteUser(uid : Int){
        Executors.newSingleThreadExecutor().execute {
            val usersRecd = database.userDao().getUserByUid(uid)
            if (usersRecd != null) {
                database.userDao().deleteUser(usersRecd)
                runOnUiThread {
                    Toast.makeText(this, "User deleted", Toast.LENGTH_SHORT).show()
                    finish()
                }
            } else {
                runOnUiThread {
                    Toast.makeText(this, "User not found", Toast.LENGTH_SHORT).show()
                }
            }

        }
    }
}