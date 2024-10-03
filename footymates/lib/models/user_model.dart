import 'package:cloud_firestore/cloud_firestore.dart';

class UserModel {
  final String firstName;
  final String lastName;
  final String email;
  String? selectedProfilePhoto; // Nullable, as user may not have a profile photo

  UserModel({
    required this.firstName,
    required this.lastName,
    required this.email,
    this.selectedProfilePhoto,
  });

  // Factory constructor to create a UserModel from Firestore snapshot
  factory UserModel.fromSnapshot(DocumentSnapshot snapshot) {
    Map<String, dynamic> data = snapshot.data() as Map<String, dynamic>;

    return UserModel(
      firstName: data['firstName'] ?? '', // Default to empty if field is missing
      lastName: data['lastName'] ?? '',   // Default to empty if field is missing
      email: data['email'] ?? '',         // Default to empty if field is missing
      selectedProfilePhoto: data['selectedProfilePhoto'], // Can be null
    );
  }

  // Method to convert the UserModel to a map (for saving to Firestore)
  Map<String, dynamic> toMap() {
    return {
      'firstName': firstName,
      'lastName': lastName,
      'email': email,
      'selectedProfilePhoto': selectedProfilePhoto, // Can be null
    };
  }
}
