#include <iostream>
#include <limits>
#include "leaderboard.h"
#include "leaderboard.cpp"

using namespace std;

int getValidatedStars(string message) {
    int stars;
    while (true) {
        cout << message;
        cin >> stars;
        if (cin.fail()) {
            cout << "Error bre : Masukkin angka aja" << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return stars;
        }
    }
}

int main() {
    PlayerNode* root = nullptr;
    int choice, stars, newStars;
    string name;

    do {
        cout << "\n=== MLBB LEADERBOARD SYSTEM ===" << endl;
        // --- BAGIAN CRUD (UTAMA) ---
        cout << "1. Input Player" << endl;       
        cout << "2. Lihat Top Global" << endl; 
        cout << "3. Cari Player" << endl;         
        cout << "4. Update Bintang Player" << endl;           
        cout << "5. Hapus Player " << endl;        
        cout << "6. Tampilkan Ascending (In-Order)" << endl;
        cout << "7. Tampilkan Pre-Order" << endl;
        cout << "8. Tampilkan Post-Order" << endl;   
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

            case 1:
                cout << "Nickname : "; cin >> name;
                stars = getValidatedStars("Bintang berapa? : ");
                root = insertPlayer(root, name, stars);
                cout << "Data dah masuk bro" << endl;
                break;

            case 2:
                cout << "\n--- TOP GLOBAL (DESCENDING / REVERSE IN-ORDER) ---" << endl;
                if (!root) cout << "Kosong." << endl;
                else {
                    int rank = 1;
                    displayLeaderboard(root, rank);
                }
                break;

            case 3: 
                stars = getValidatedStars("Cari bintang berapa? : ");
                searchPlayerByStars(root, stars);
                break;

            case 4: 
                stars = getValidatedStars("Bintang LAMA brp? : ");
                cout << "Verifikasi Nickname : "; cin >> name;
                newStars = getValidatedStars("Bintang BARU brp? : ");
                root = updatePlayerStars(root, stars, newStars, name);
                break;

            case 5: 
                stars = getValidatedStars("Hapus player bintang brp? : ");
                root = deletePlayer(root, stars);
                cout << "Player dihapus (kalo emang ada datanya)." << endl;
                break;

            case 6: 
                cout << "\n-- URUTAN BINTANG TERKECIL (IN-ORDER) --" << endl;
                //ini buat mastiin tree terurut
                if (!root) cout << "Kosong." << endl;
                else displayInOrder(root);
                break;

            case 7: 
                cout << "\n-- STRUKTUR PRE-ORDER (ROOT DULU) --" << endl;
                if (!root) cout << "Kosong." << endl;
                else displayPreOrder(root);
                break;

            case 8: 
                cout << "\n-- STRUKTUR POST-ORDER (ANAK DULU) --" << endl;
                if (!root) cout << "Kosong." << endl;
                else displayPostOrder(root);
                break;

            case 9:
                cout << "bye bye..." << endl;
                break;
                
            default:
                cout << "Pilihan ga ada bre." << endl;
        }
    } while (choice != 9);

    return 0;
}