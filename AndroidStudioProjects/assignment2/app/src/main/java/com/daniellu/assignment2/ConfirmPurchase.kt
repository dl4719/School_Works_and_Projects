package com.daniellu.assignment2

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.Spinner
import android.widget.TextView

class ConfirmPurchase : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        val confirmFrag : View = inflater.inflate(
            R.layout.fragment_confirm_purchase,
            container,
            false
        )

        val tvItemPurchased : TextView = confirmFrag.findViewById(R.id.tvItemPurchased)
        val tvItemPrice : TextView = confirmFrag.findViewById(R.id.tvItemPrice)

        val itemName = arguments?.getString("key_prodName")
        val itemPrice = arguments?.getString("key_prodPrice")

        tvItemPurchased.text = itemName
        tvItemPrice.text = itemPrice

        val spinnerQty : Spinner = confirmFrag.findViewById(R.id.spinnerQty)
        val quantity = listOf(1,2,3,4,5,6,7,8,9)

        val adapter = ArrayAdapter(
            requireActivity(),
            android.R.layout.simple_spinner_item,
            quantity
        )
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_item)
        spinnerQty.adapter = adapter


        val btnFinalize : Button = confirmFrag.findViewById(R.id.btnFinalize)

        btnFinalize.setOnClickListener {
            val prodBundle : Bundle = Bundle()

            var prodNameData : String = tvItemPurchased.text.toString().trim()
            var prodPriceData : String = tvItemPrice.text.toString().trim()
            var prodQuantityData : String = spinnerQty.selectedItem.toString().trim()

            prodBundle.putString("key_nameData", prodNameData)
            prodBundle.putString("key_priceData", prodPriceData)
            prodBundle.putString("key_qtyData", prodQuantityData)

            val thankYouFrag = ThankYou()
            thankYouFrag.arguments = prodBundle

            requireActivity().supportFragmentManager.popBackStack()
            requireActivity().supportFragmentManager.beginTransaction()
                .replace(R.id.flConfirmation, thankYouFrag)
                .addToBackStack(null)
                .commit()
        }

        return confirmFrag
    }

}