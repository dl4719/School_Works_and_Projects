package com.example.assignment3

import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [User::class], version = 1)
abstract class AppUserDatabase : RoomDatabase() {
    abstract fun userDao(): UserDao
}