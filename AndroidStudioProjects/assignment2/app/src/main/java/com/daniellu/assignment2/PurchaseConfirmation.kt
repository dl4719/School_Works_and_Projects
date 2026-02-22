package com.daniellu.assignment2

import android.os.Bundle
import android.util.Log
import android.widget.ImageView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentTransaction

class PurchaseConfirmation : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_purchase_confirmation)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
        val prodName : String = intent.getStringExtra("key_prodName").toString()
        val prodPrice : String = intent.getStringExtra("key_prodPrice").toString()

        val summaryBundle : Bundle = Bundle()
        summaryBundle.putString("key_prodName", prodName)
        summaryBundle.putString("key_prodPrice", prodPrice)

        val confirmFrag = ConfirmPurchase()
        confirmFrag.arguments = summaryBundle

        loadFragment(confirmFrag)

        Log.d("LIFECYCLE", "PurchaseConfirmation onCreate")
    }

    fun loadFragment(fragment: Fragment) {
        val fm : FragmentManager = supportFragmentManager
        val ft : FragmentTransaction = fm.beginTransaction()
        fm.popBackStack()
        ft.add(R.id.flConfirmation, fragment)
        ft.addToBackStack(null)
        ft.commit()
    }

    override fun onStart() {
        super.onStart()
        Log.d("LIFECYCLE", "PurchaseConfirmation onStart")
    }

    override fun onResume() {
        super.onResume()
        Log.d("LIFECYCLE", "PurchaseConfirmation onResume")
    }

    override fun onPause() {
        super.onPause()
        Log.d("LIFECYCLE", "PurchaseConfirmation onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.d("LIFECYCLE", "PurchaseConfirmation onStop")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d("LIFECYCLE", "PurchaseConfirmation onDestroy")
    }

    override fun onRestart() {
        super.onRestart()
        Log.d("LIFECYCLE", "PurchaseConfirmation onRestart")
    }
}