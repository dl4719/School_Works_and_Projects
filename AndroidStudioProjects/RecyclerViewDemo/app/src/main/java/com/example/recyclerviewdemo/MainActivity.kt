package com.example.recyclerviewdemo

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

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

        val contactsRecyclerView : RecyclerView = findViewById(R.id.contactsRecyclerView)

        val empList : ArrayList<Employee> = ArrayList()

        ///////// calling API ///////// db call ///////// sample data for now /////////
        val emp = Employee(
            R.drawable.ic_launcher_background,
            "Jenny",
            "jenny@gmail.com"
        )
        empList.add(emp)

        //// Better way to implement code above ////

        for (i in 1..100) {
            empList.add(
                Employee(
                    R.drawable.ic_launcher_background,
                    "John $i",
                    "johndoe@gmail.com"
                )
            )
        }

        // val employeeAdapter = EmployeeAdapter(this, empList) // take the implementation and add it to the adapter instead to save memory

        contactsRecyclerView.adapter = EmployeeAdapter(this, empList)
        contactsRecyclerView.layoutManager = LinearLayoutManager(this)
    }
}