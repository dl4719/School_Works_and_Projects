package com.daniellu.fragmentsdemo

import android.os.Bundle
import android.widget.Button
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentTransaction

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val btnSignUp : Button = findViewById(R.id.btnSignUp)
        val btnLogin : Button = findViewById(R.id.btnLogin)

        btnLogin.setOnClickListener {
            val loginFragment = LoginFragment()

            val fm : FragmentManager = supportFragmentManager
            val ft : FragmentTransaction = fm.beginTransaction()
            fm.popBackStack()
            ft.add(R.id.flLogin, loginFragment)
            ft.addToBackStack(null)
            ft.commit()
        }
    }
}