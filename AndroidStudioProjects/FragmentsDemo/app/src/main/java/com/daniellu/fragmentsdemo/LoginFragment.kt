package com.daniellu.fragmentsdemo

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import android.widget.TextView

class LoginFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val loginFragment : View = inflater.inflate(
            R.layout.fragment_login,
            container,
            false
        )

        val etEmail : EditText = loginFragment.findViewById(R.id.etEmail)
        val tvGoToSignUp : TextView = loginFragment.findViewById(R.id.tvGoToSignUp)

        tvGoToSignUp.setOnClickListener {
            val emailData = etEmail.text.toString().trim()

            val bundleSendEmailData : Bundle = Bundle()
            bundleSendEmailData.putString("key_email", emailData)

            val signUpFragment = SignUpFragment()

            signUpFragment.arguments
        }

        return loginFragment
    }


}