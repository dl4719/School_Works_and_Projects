package com.example.assignment3

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.RecyclerView.Recycler
import kotlin.math.ln

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

        val rvDisplayAllUsers : RecyclerView = findViewById(R.id.rvDisplayAllUsers)

        val userList : ArrayList<User> = ArrayList()

        val fName = intent.getStringExtra("key_fName").toString()
        val lName = intent.getStringExtra("key_lName").toString()
        val email = intent.getStringExtra("key_email").toString()

        userList.add(
            User(
                firstName = fName,
                lastName = lName,
                email = email
            )

        )

        rvDisplayAllUsers.adapter = UserAdapter(this, userList)
        rvDisplayAllUsers.layoutManager = LinearLayoutManager(this)
    }
}