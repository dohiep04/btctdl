#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>

using namespace std;

class DoThi {
public:
    int dinh;
    vector<vector<int>> maTranLanCan;
    map<int, vector<int>> danhSachLanCan;

    DoThi(int soDinh) {
        dinh = soDinh;
        maTranLanCan.resize(dinh, vector<int>(dinh, 0));
    }

    void themCanh(int u, int v) {
        maTranLanCan[u][v] = 1;
        maTranLanCan[v][u] = 1;
        danhSachLanCan[u].push_back(v);
        danhSachLanCan[v].push_back(u);
    }

    void hienThiMaTranLanCan() {
        cout << "\nMa tran lan can:" << endl;
        for (const auto &hang : maTranLanCan) {
            for (int giaTri : hang) {
                cout << giaTri << " ";
            }
            cout << endl;
        }
    }

    void hienThiDanhSachLanCan() {
        cout << "\nDanh sach lan can:" << endl;
        for (const auto &cap : danhSachLanCan) {
            cout << cap.first << ": ";
            for (int giaTri : cap.second) {
                cout << giaTri << " ";
            }
            cout << endl;
        }
    }

    vector<int> bfs(int batDau) {
        vector<bool> daTham(dinh, false);
        queue<int> hangDoi;
        vector<int> ketQua;

        hangDoi.push(batDau);
        daTham[batDau] = true;

        while (!hangDoi.empty()) {
            int dinhHienTai = hangDoi.front();
            hangDoi.pop();
            ketQua.push_back(dinhHienTai);

            for (int lanCan : danhSachLanCan[dinhHienTai]) {
                if (!daTham[lanCan]) {
                    hangDoi.push(lanCan);
                    daTham[lanCan] = true;
                }
            }
        }

        return ketQua;
    }

    vector<int> dfs(int batDau) {
        vector<bool> daTham(dinh, false);
        stack<int> nganXep;
        vector<int> ketQua;

        nganXep.push(batDau);

        while (!nganXep.empty()) {
            int dinhHienTai = nganXep.top();
            nganXep.pop();

            if (!daTham[dinhHienTai]) {
                daTham[dinhHienTai] = true;
                ketQua.push_back(dinhHienTai);

                for (auto it = danhSachLanCan[dinhHienTai].rbegin(); it != danhSachLanCan[dinhHienTai].rend(); ++it) {
                    if (!daTham[*it]) {
                        nganXep.push(*it);
                    }
                }
            }
        }

        return ketQua;
    }
};

int main() {
    int soDinh = 9;
    DoThi doThi(soDinh);

    vector<pair<int, int>> canh = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5},
        {4, 6}, {5, 7}, {6, 8}, {7, 8}
    };

    for (const auto &c : canh) {
        doThi.themCanh(c.first, c.second);
    }

    doThi.hienThiMaTranLanCan();
    doThi.hienThiDanhSachLanCan();

    int batDau = 0;
    vector<int> ketQuaBFS = doThi.bfs(batDau);
    vector<int> ketQuaDFS = doThi.dfs(batDau);

    cout << "\nThu tu cac dinh duyet BFS: ";
    for (int dinh : ketQuaBFS) {
        cout << dinh << " ";
    }

    cout << "\nThu tu cac dinh duyet DFS: ";
    for (int dinh : ketQuaDFS) {
        cout << dinh << " ";
    }

    return 0;
}

