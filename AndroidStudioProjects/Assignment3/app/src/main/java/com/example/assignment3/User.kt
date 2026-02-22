package com.example.assignment3

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "users")
data class User(
    @PrimaryKey(autoGenerate = true)
    @ColumnInfo(name = "primary_key") val uid: Int = 0,
    @ColumnInfo(name = "userProfile") val profileImageRes: Int = R.drawable.ic_launcher_foreground,
    @ColumnInfo(name = "first_name") val firstName: String,
    @ColumnInfo(name = "last_name") val lastName: String,
    @ColumnInfo(name = "user_email") val email: String

)
