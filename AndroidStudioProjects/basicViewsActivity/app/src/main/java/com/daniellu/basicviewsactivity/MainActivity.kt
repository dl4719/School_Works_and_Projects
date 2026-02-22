package com.daniellu.basicviewsactivity

import android.content.Intent
import android.os.Bundle
import android.provider.MediaStore
import android.util.Log
import android.widget.Button
import android.widget.CheckBox
import android.widget.EditText
import android.widget.RadioButton
import android.widget.RadioGroup
import android.widget.TextView
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

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

        val tvOutput : TextView = findViewById(R.id.tvOutput)

        val etFirstName : EditText = findViewById(R.id.etFirstName)
        val etLastName : EditText = findViewById(R.id.etLastName)
        val etEmail : EditText = findViewById(R.id.etEmail)

        val btnRegister : Button = findViewById(R.id.btnRegister)
        val btnShowDetails : Button = findViewById(R.id.btnShowDetails)

        val rgGender : RadioGroup = findViewById(R.id.rgGender)

        val rbMale : RadioButton = findViewById(R.id.rbMale)
        val rbFemale : RadioButton = findViewById(R.id.rbFemale)
        val rbOther : RadioButton = findViewById(R.id.rbOther)

        val cbAgree : CheckBox = findViewById(R.id.cbAgree)

        cbAgree.setOnCheckedChangeListener { buttonView, isChecked ->
            Toast.makeText(
                this,
                "The value of I agree Cb is $isChecked",
                Toast.LENGTH_SHORT
            ).show()
        }

        rbMale.setOnCheckedChangeListener { buttonView, isChecked ->
            Toast.makeText(
                this,
                "The value of rbMale is $isChecked",
                Toast.LENGTH_SHORT
            ).show()
        }

        btnShowDetails.setOnClickListener {
            /*val rbSelectedId = rgGender.checkedRadioButtonId

            val rbSelected : RadioButton = findViewById(rbSelectedId)

            val genderSelected : String = rbSelected.text.toString().trim()*/

            val rbSel : RadioButton = findViewById(rgGender.checkedRadioButtonId)

            /*val cbValue : Boolean = cbAgree.isChecked*/


            Toast.makeText(
                this,
                "The value of Gender Selected is ${rbSel.text.toString()} " +
                        "and checkbox value is ${cbAgree.isChecked}",
                Toast.LENGTH_SHORT
            ).show()
        }

        btnRegister.setOnClickListener {
            var fName : String = etFirstName.text.toString().trim()
            var lName : String = etLastName.text.toString().trim()

            tvOutput.text = "$fName $lName \n${etEmail.text.toString().trim()}"

            val secondActivityIntent = Intent(
                applicationContext,
                Activity2::class.java
            )
            secondActivityIntent.putExtra("key_fName", fName)
            startActivity(secondActivityIntent)

            /*Toast.makeText(
                applicationContext,
                "User added text " + etFirstName.text.toString(),
                Toast.LENGTH_SHORT
            ).show()*/
        }
        Log.d("LIFECYCLE", "Main Activity onCreate")
    }

    override fun onStart() {
        super.onStart()
        Log.d("LIFECYCLE", "Main Activity onStart")
    }

    override fun onResume() {
        super.onResume()
        Log.d("LIFECYCLE", "Main Activity onResume")
    }

    override fun onPause() {
        super.onPause()
        Log.d("LIFECYCLE", "Main Activity onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.d("LIFECYCLE", "Main Activity onStop")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d("LIFECYCLE", "Main Activity onDestroy")
    }

    override fun onRestart() {
        super.onRestart()
        Log.d("LIFECYCLE", "Main Activity onRestart")
    }
}