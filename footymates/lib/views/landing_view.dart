import 'package:flutter/material.dart';
import '../../controllers/auth_controller.dart';

class LoginSignupPage extends StatelessWidget {
  final AuthController _authController = AuthController();

  LoginSignupPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Welcome Text
            Padding(
              padding: const EdgeInsets.only(bottom: 20.0),
              child: Text(
                'Welcome to FootyMates!',
                style: TextStyle(
                  fontSize: 24,
                  fontWeight: FontWeight.bold,
                  color: const Color.fromARGB(255, 235, 32, 32), // Adjust color to match your theme
                ),
              ),
            ),

            // Logo
            Padding(
              padding: const EdgeInsets.only(bottom: 50.0),
              child: Image.asset(
                'assets/footylogo.png', // Ensure the logo image is in the assets folder
                height: 300,
                width: 300,
              ),
            ),

            // Log In Button
            ElevatedButton(
              onPressed: () {
                // Redirect to login functionality
              },
              style: ElevatedButton.styleFrom(
                padding: const EdgeInsets.symmetric(horizontal: 40, vertical: 15),
              ),
              child: const Text('Log In'),
            ),

            const SizedBox(height: 20),

            // Sign Up Button
            ElevatedButton(
              onPressed: () {
                // Redirect to sign-up functionality
              },
              style: ElevatedButton.styleFrom(
                padding: const EdgeInsets.symmetric(horizontal: 40, vertical: 15),
              ),
              child: const Text('Sign Up'),
            ),
          ],
        ),
      ),
    );
  }
}
