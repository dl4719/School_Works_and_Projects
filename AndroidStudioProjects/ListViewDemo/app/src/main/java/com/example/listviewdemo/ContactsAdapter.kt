package com.example.listviewdemo

import android.annotation.SuppressLint
import android.app.Activity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ImageView
import android.widget.TextView


class ContactsAdapter(
    private val context : Activity,
    private val contactsArrayList : ArrayList<Contacts>
) : ArrayAdapter<Contacts>(context, R.layout.list_item, contactsArrayList) {

    //@SuppressLint("InflateParams", "ViewHolder")
    override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {

        val inflater : LayoutInflater = LayoutInflater.from(context)
        val view : View = inflater.inflate(R.layout.list_item, null)

        val listItemImageView : ImageView = view.findViewById(R.id.listItemImageView)
        val listItemContactName : TextView = view.findViewById(R.id.listItemContactName)
        val listItemContactEmail : TextView = view.findViewById(R.id.listItemContactEmail)

        listItemImageView.setImageResource(contactsArrayList[position].imageId)
        listItemContactName.text = contactsArrayList[position].contactName
        listItemContactEmail.text = contactsArrayList[position].contactEmail


        return view
    }
}