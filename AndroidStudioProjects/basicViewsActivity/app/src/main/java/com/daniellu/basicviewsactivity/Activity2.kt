package com.daniellu.basicviewsactivity

import android.os.Bundle
import android.util.Log
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class Activity2 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_2)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val tvIntentData : TextView = findViewById(R.id.tvIntentData)

        tvIntentData.text = intent.getStringExtra("key_fName")

        Log.d("LIFECYCLE", "Activity2 onCreate")
    }

    override fun onStart() {
        super.onStart()
        Log.d("LIFECYCLE", "Activity2 onStart")
    }

    override fun onResume() {
        super.onResume()
        Log.d("LIFECYCLE", "Activity2 onResume")
    }

    override fun onPause() {
        super.onPause()
        Log.d("LIFECYCLE", "Activity2 onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.d("LIFECYCLE", "Activity2 onStop")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d("LIFECYCLE", "Activity2 onDestroy")
    }

    override fun onRestart() {
        super.onRestart()
        Log.d("LIFECYCLE", "Activity2 onRestart")
    }
}