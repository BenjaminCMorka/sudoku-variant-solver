// lib/controllers/auth_controller.dart

import '../models/user_model.dart';

class AuthController {
  void login(UserModel user) {
    // Handle login logic
    print("User logged in with email: ${user.email}");
  }

  void signUp(UserModel user) {
    // Handle signup logic
    print("User signed up with email: ${user.email}");
  }
}
