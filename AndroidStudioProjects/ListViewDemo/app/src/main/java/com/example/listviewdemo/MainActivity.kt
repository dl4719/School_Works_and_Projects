package com.example.listviewdemo

import android.os.Bundle
import android.widget.ListView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class MainActivity : AppCompatActivity() {

    private lateinit var contactsArrayList : ArrayList<Contacts>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val contactsListView : ListView = findViewById(R.id.contactsListView)

        contactsArrayList = ArrayList()

        val contact1 = Contacts(
            R.drawable.feixiao,
            "Feixiao",
            "feixiao@gmail.com"
        )

        contactsArrayList.add(contact1)

        // Save memory by putting the previous steps into one
        contactsArrayList.add(
            Contacts(
                R.drawable.citlali,
                "Citlali",
                "grannyitzili@gmail.com"
            )
        )

        for (i in 1..20) {
            contactsArrayList.add(
                Contacts(
                    R.drawable.arlecchino,
                    "Arlecchino $i",
                    "knaive@gmail.com"
                )
            )
        }
        /////////////////////////////////////////////

        val contactsAdapter = ContactsAdapter(this, contactsArrayList)
        contactsListView.adapter = contactsAdapter
    }
}