#include <iostream>
#include "leaderboard.h"

// Logika nentuin Tier Mobile Legends
string getRankTitle(int stars) {
    if (stars >= 100) return "MYTHICAL IMMORTAL";
    if (stars >= 50)  return "MYTHICAL GLORY";
    if (stars >= 25)  return "MYTHIC HONOR";
    return "MYTHIC MAWI"; // 0-24 Bintang
}

// Fungsi membuat Node baru
PlayerNode* createPlayer(string name, int stars) {
    PlayerNode* newPlayer = new PlayerNode();
    newPlayer->name = name;
    newPlayer->stars = stars;
    newPlayer->left = nullptr;
    newPlayer->right = nullptr;
    return newPlayer;
}

// Input Player (Insert)
// Logika: Bintang kecil ke Kiri, Bintang besar ke Kanan
PlayerNode* insertPlayer(PlayerNode* root, string name, int stars) {
    // Jika posisi kosong, tempati di sini
    if (root == nullptr) {
        return createPlayer(name, stars);
    }
    
    // Rekursif untuk mencari posisi yang pas
    if (stars < root->stars) 
        root->left = insertPlayer(root->left, name, stars);
    else 
        root->right = insertPlayer(root->right, name, stars);
        
    return root;
}

// menampilkan/Lihat TOP GLOBAL (Traversal)
// Menggunakan Reverse In-Order (Kanan -> Root -> Kiri)
void displayLeaderboard(PlayerNode* root, int& rank) {
    if (root != nullptr) {
        // 1. Kunjungi Kanan (Bintang Terbanyak)
        displayLeaderboard(root->right, rank);
        
        // 2. menampilkan Data
        cout << rank << ". " << root->name 
             << " \t| " << getRankTitle(root->stars) 
             << " (" << root->stars << " Bintang)" << endl;
             
        rank++; 
        
        // 3. Kunjungi Kiri (Bintang Lebih Sedikit)
        displayLeaderboard(root->left, rank);
    }
} 

// IN-ORDER (Left -> Root -> Right)
// Urut dari Bintang Terkecil ke Terbesar (Ascending)
void displayInOrder(PlayerNode* root) {
    if (root != nullptr) {
        displayInOrder(root->left);
        cout << "[ " << root->stars << " Bintang ] " << root->name << endl;
        displayInOrder(root->right);
    }
}

// PRE-ORDER (Root -> Left -> Right)
// Mencetak Induk dulu, baru anak-anaknya.
void displayPreOrder(PlayerNode* root) {
    if (root != nullptr) {
        cout << "[ " << root->stars << " Bintang ] " << root->name << endl;
        displayPreOrder(root->left);
        displayPreOrder(root->right);
    }
}

// POST-ORDER (Left -> Right -> Root)
// Hasil: Mencetak anak-anak dulu, Induk terakhir.
void displayPostOrder(PlayerNode* root) {
    if (root != nullptr) {
        displayPostOrder(root->left);
        displayPostOrder(root->right);
        cout << "[ " << root->stars << " Bintang ] " << root->name << endl;
    }
}

// mencari node paling kiri (terkecil) buat bantu delete
PlayerNode* minValueNode(PlayerNode* node) {
    PlayerNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// mencari node by stars buat validasi update
PlayerNode* findNodeByStars(PlayerNode* root, int stars) {
    if (root == nullptr || root->stars == stars) return root;
    if (stars < root->stars) return findNodeByStars(root->left, stars);
    return findNodeByStars(root->right, stars);
}

// Fitur Search
void searchPlayerByStars(PlayerNode* root, int targetStars) {
    if (root == nullptr) {
        cout << "Player dengan " << targetStars << " bintang ga ketemu bre." << endl;
        return;
    }
    if (root->stars == targetStars) {
        cout << "KETEMU: " << root->name 
             << " [" << getRankTitle(root->stars) << "]" << endl;
    } 
    else if (targetStars < root->stars) {
        searchPlayerByStars(root->left, targetStars);
    } 
    else {
        searchPlayerByStars(root->right, targetStars);
    }
}

// Fitur Delete
PlayerNode* deletePlayer(PlayerNode* root, int stars) {
    if (root == nullptr) return root;

    if (stars < root->stars) root->left = deletePlayer(root->left, stars);
    else if (stars > root->stars) root->right = deletePlayer(root->right, stars);
    else {
        // Node ketemu, saatnya dihapus
        if (root->left == nullptr) {
            PlayerNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            PlayerNode* temp = root->left;
            delete root;
            return temp;
        }
        // Kasus 2 anak (ambil successor)
        PlayerNode* temp = minValueNode(root->right);
        root->stars = temp->stars;
        root->name = temp->name;
        root->right = deletePlayer(root->right, temp->stars);
    }
    return root;
}

// Fitur Update
PlayerNode* updatePlayerStars(PlayerNode* root, int oldStars, int newStars, string name) {
    PlayerNode* target = findNodeByStars(root, oldStars);
    
    if (target == nullptr) {
        cout << "Gagal bre : Bintang " << oldStars << " ga ada datanya." << endl;
        return root;
    }
    
    if (target->name != name) {
        cout << "Gagal bre : Bintang " << oldStars << " itu punya '" << target->name 
             << "', bukan punya '" << name << "'." << endl;
        return root;
    }

    root = deletePlayer(root, oldStars);
    root = insertPlayer(root, name, newStars);
    cout << "Sukses update bintang si " << name << " bro!" << endl;
    
    return root;
}