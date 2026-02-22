package com.daniellu.assignment2

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class Menu : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_menu)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val btnDuck : Button = findViewById(R.id.btnDuck)
        val btnDog : Button = findViewById(R.id.btnDog)
        val btnCat : Button = findViewById(R.id.btnCat)

        btnDuck.setOnClickListener {
            val confirmationIntent = Intent(
                applicationContext,
                PurchaseConfirmation::class.java
            )

            val itemName : TextView = findViewById(R.id.tvDuck)
            val itemPrice : TextView = findViewById(R.id.tvDuckPrice)

            sendToConfirmation(itemName, itemPrice, confirmationIntent)
        }

        btnDog.setOnClickListener {
            val confirmationIntent = Intent(
                applicationContext,
                PurchaseConfirmation::class.java
            )

            val itemName : TextView = findViewById(R.id.tvDog)
            val itemPrice : TextView = findViewById(R.id.tvDogPrice)

            sendToConfirmation(itemName, itemPrice,confirmationIntent)
        }

        btnCat.setOnClickListener {
            val confirmationIntent = Intent(
                applicationContext,
                PurchaseConfirmation::class.java
            )

            val itemName : TextView = findViewById(R.id.tvCat)
            val itemPrice : TextView = findViewById(R.id.tvCatPrice)

                sendToConfirmation(itemName, itemPrice, confirmationIntent)
        }

        Log.d("LIFECYCLE", "Menu onCreate")
    }

    fun sendToConfirmation(
        itemName : TextView,
        itemPrice : TextView,
        confirm : Intent
    ) {
        val prodName : String = itemName.text.toString().trim()
        val prodPrice : String = itemPrice.text.toString().trim()

        confirm.putExtra("key_prodName", prodName)
        confirm.putExtra("key_prodPrice", prodPrice)

        startActivity(confirm)
    }

    override fun onStart() {
        super.onStart()
        Log.d("LIFECYCLE", "Menu onStart")
    }

    override fun onResume() {
        super.onResume()
        Log.d("LIFECYCLE", "Menu onResume")
    }

    override fun onPause() {
        super.onPause()
        Log.d("LIFECYCLE", "Menu onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.d("LIFECYCLE", "Menu onStop")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d("LIFECYCLE", "Menu onDestroy")
    }

    override fun onRestart() {
        super.onRestart()
        Log.d("LIFECYCLE", "Menu onRestart")
    }
}