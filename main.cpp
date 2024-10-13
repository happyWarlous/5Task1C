#include <iostream>
#include <vector>
#include <queue>
#include <set>

bool is_complete(const std::vector<int> &pile) {
  return pile == std::vector<int>{14, 13, 12, 11, 10, 9, 8, 7, 6};
}

std::pair<bool, int> CanClearAllPiles(std::vector<std::vector<int>> &piles)
{
  std::queue<std::pair<std::vector<std::vector<int>>, int>> q;
  std::set<std::vector<std::vector<int>>> visited;

  q.push({piles, 0});

  while (!q.empty()) {
    auto [current_piles, moves] = q.front();
    q.pop();

    bool all_removed = true;
    for (const auto &pile : current_piles) {
      if (!is_complete(pile)) {
        all_removed = false;
        break;
      }
    }

    if (all_removed) {
      return {true, moves};
    }

    for (int64_t i = 0; i < current_piles.size(); i++) {
      if (!current_piles[i].empty()) {
        int card = current_piles[i].back();
        for (int64_t j = 0; j < current_piles.size(); j++) {
          if (i != j && !current_piles[j].empty()) {
            if (current_piles[j].back() > card) {
              std::vector<std::vector<int>> new_piles = current_piles;
              new_piles[j].push_back(card);
              new_piles[i].pop_back();

              if (!new_piles[i].empty()) {
                visited.insert(new_piles);
                q.push({new_piles, moves + 1});
              }
            }
          }
        }
      }
    }
  }

  return {false, 0};
}

int main() {
  std::ios::sync_with_stdio(false);

  std::vector<std::vector<int>> piles(8);

  for (int i = 0; i < 8; i++) {
    piles[i].resize(9);
    std::cout << "Введите карты в " << i + 1 << " куче (от 6 до туза, где 6 = 6, 7 = 7, ..., 14 = туз): ";
    for (int j = 0; j < 9; j++) {
      std::cin >> piles[i][j];
    }
  }

  auto [result, min_moves] = CanClearAllPiles(piles);
  if (result) {
    std::cout << "Можно убрать все карты. Количество действий: " << min_moves << "." << '\n';
  }
  else {
    std::cout << "Невозможно убрать все карты." << '\n';
  }

  return 0;
}
