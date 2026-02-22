package com.daniellu.fragmentsdemo

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import kotlinx.coroutines.newSingleThreadContext
import kotlin.math.sign

class SignUpFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val signUpFragView : View = inflater.inflate(
            R.layout.fragment_sign_up,
            container,
            false
        )

        val tv : TextView = signUpFragView.findViewById(R.id.tvDataRead)

        return signUpFragView
    }

}