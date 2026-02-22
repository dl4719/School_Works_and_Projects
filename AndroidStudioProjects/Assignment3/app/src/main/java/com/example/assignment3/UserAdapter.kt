package com.example.assignment3

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.recyclerview.widget.RecyclerView

class UserAdapter(val context : Context, val userList : List<User>) : RecyclerView.Adapter<UserAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(
            R.layout.user_list_item,
            parent,
            false
        )

        return ViewHolder(view)
    }

    override fun getItemCount(): Int {
        return userList.size
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.tvUserName.text = "${userList[position].firstName} ${userList[position].lastName}"

        holder.tvUserEmail.text = userList[position].email

        holder.userProfile.setImageResource(userList[position].profileImageRes)

        holder.itemView.setOnClickListener{
            Toast.makeText(
                context,
                "${userList[position].firstName} ${userList[position].lastName}",
                Toast.LENGTH_SHORT
            ).show()

            val userDetailsIntent = Intent(
                context,
                UserDetailsActivity::class.java
            )

            userDetailsIntent.putExtra("key_userProfile", userList[position].profileImageRes)
            userDetailsIntent.putExtra("key_uid", userList[position].uid)
            userDetailsIntent.putExtra("key_fName", userList[position].firstName)
            userDetailsIntent.putExtra("key_lName", userList[position].lastName)
            userDetailsIntent.putExtra("key_email", userList[position].email)

            context.startActivity(userDetailsIntent)
        }
    }


    class ViewHolder(view : View) : RecyclerView.ViewHolder(view){
        val tvUserName : TextView = view.findViewById(R.id.tvUserName)
        val tvUserEmail : TextView = view.findViewById(R.id.tvUserEmail)
        val userProfile : ImageView = itemView.findViewById(R.id.profileImageView)

    }
}