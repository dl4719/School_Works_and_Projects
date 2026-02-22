package com.daniellu.assignment2

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView

class ThankYou : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val thankYouFrag : View = inflater.inflate(
            R.layout.fragment_thank_you,
            container,
            false
        )

        val tvProdName : TextView = thankYouFrag.findViewById(R.id.tvProdName)
        val tvProdPrice : TextView = thankYouFrag.findViewById(R.id.tvProdPrice)
        val tvProdQty : TextView = thankYouFrag.findViewById(R.id.tvProdQty)

        val prodName = arguments?.getString("key_nameData")
        val prodPrice = arguments?.getString("key_priceData")
        val prodQty = arguments?.getString("key_qtyData")

        tvProdName.text = "Name: ${prodName}"
        tvProdPrice.text = "Price: ${prodPrice}"
        tvProdQty.text = "Quantity Ordered: ${prodQty}"

        return thankYouFrag
    }

}