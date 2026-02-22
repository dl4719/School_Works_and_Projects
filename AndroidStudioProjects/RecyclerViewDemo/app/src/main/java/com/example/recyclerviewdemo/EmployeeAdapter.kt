package com.example.recyclerviewdemo

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.core.content.contentValuesOf
import androidx.recyclerview.widget.RecyclerView

class EmployeeAdapter(val context: Context, val empList : ArrayList<Employee>) : RecyclerView.Adapter<EmployeeAdapter.ViewHolder>() {


    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(
            R.layout.list_item,
            parent,
            false
        )

        return ViewHolder(view)
    }

    override fun getItemCount(): Int {
        return empList.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.imageView.setImageResource(empList[position].imageId)
        holder.tvEmpName.text = empList[position].empName
        holder.tvEmpEmail.text = empList[position].empEmail

        holder.itemView.setOnClickListener{
            Toast.makeText(context, empList[position].empName, Toast.LENGTH_SHORT).show()

            val empDetailsIntent = Intent(context, EmployeeDetailsActivity::class.java)
            // put extras
            context.startActivity(empDetailsIntent)
        }
    }

    class ViewHolder(view : View) : RecyclerView.ViewHolder(view){
        val imageView : ImageView = view.findViewById(R.id.imageView)
        val tvEmpEmail : TextView = view.findViewById(R.id.tvEmpEmail)
        val tvEmpName : TextView = view.findViewById(R.id.tvEmpName)

    }
}