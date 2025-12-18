#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
using namespace std;

// Struktur Data Node
struct PlayerNode {
    string name;
    int stars;
    PlayerNode* left;
    PlayerNode* right;
};

// Fungsi Logika Tier
string getRankTitle(int stars);

// Fitur Dasar
PlayerNode* createPlayer(string name, int stars);
PlayerNode* insertPlayer(PlayerNode* root, string name, int stars);

// update travelsal
void displayLeaderboard(PlayerNode* root, int& rank); // Ini sebenarnya Reverse In-Order
void displayInOrder(PlayerNode* root);   // Ascending/urutan (Kecil ke Besar)
void displayPreOrder(PlayerNode* root);  // Root(induk) -> Kiri -> Kanan / induk dlu
void displayPostOrder(PlayerNode* root); // Kiri -> Kanan -> Root / anak dlu


void searchPlayerByStars(PlayerNode* root, int targetStars); // Cari Player
PlayerNode* deletePlayer(PlayerNode* root, int stars);       // Hapus Player
PlayerNode* updatePlayerStars(PlayerNode* root, int oldStars, int newStars, string name); // Update Bintang
PlayerNode* minValueNode(PlayerNode* node);  // Helper cari node terkecil
PlayerNode* findNodeByStars(PlayerNode* root, int stars); // Helper cari node

#endif