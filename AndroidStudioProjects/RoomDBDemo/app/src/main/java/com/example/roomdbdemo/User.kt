package com.example.roomdbdemo

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "users")
data class User(
    @PrimaryKey(autoGenerate = true)
    val uid: Int = 0,
    val firstName: String,
    val lastName: String,
    val email: String
)

