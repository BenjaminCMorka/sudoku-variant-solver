import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'views/landing_view.dart'; // Import the login/signup view

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(const FootyMatesApp());
}

class FootyMatesApp extends StatelessWidget {
  const FootyMatesApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Footymates',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.red),
        scaffoldBackgroundColor: Colors.white,
        useMaterial3: true,
      ),
      // Show the login/signup page as the home page
      home: LoginSignupPage(),
    );
  }
}
