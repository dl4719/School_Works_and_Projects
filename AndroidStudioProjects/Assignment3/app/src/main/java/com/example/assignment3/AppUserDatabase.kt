package com.example.assignment3

import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [User::class], version = 3)
abstract class AppUserDatabase : RoomDatabase() {
    abstract fun userDao(): UserDao
}