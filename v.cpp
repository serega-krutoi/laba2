#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>

using namespace std;

ostream& operator<<(ostream& os, const vector<string>& v) {
    if (v.empty()) return os;
    for (size_t i = 0; i + 1 < v.size(); ++i) {
        os << v[i] << " ";
    }
    os << v.back();
    return os;
}

// Описание одного человека
struct Person {
    string parent;              // имя родителя
    vector<string> children;    // имена детей по порядку рождения
    bool kingStatus;            // отмечен ли король
    bool aliveStatus;           // жив или нет

    Person() : parent(""), kingStatus(false), aliveStatus(true) {}
};

class ThroneInheritance {
    unordered_map<string, Person> people; // все люди по имени
    string kingName;                      // имя короля

    // проверка длины имени (ограничение из ТЗ)
    bool name_ok(const string& n) const {
        int sz = static_cast<int>(n.size());
        return (1 <= sz && sz <= 15);
    }

    // проверка: входит ли name в curOrder
    bool inOrder(const string& name, const vector<string>& curOrder) const {
        for (const string& s : curOrder) {
            if (s == name) return true;
        }
        return false;
    }

    // рекурсивная функция 
    // Successor(x, curOrder) возвращает имя следующего в порядке
    // или пустую строку, если кандидатов больше нет
    string Successor(const string& x, const vector<string>& curOrder) const {
        auto it = people.find(x);
        if (it == people.end()) return "";

        const Person& p = it->second;

        // если нет детей или все дети уже присутствуют в curOrder
        bool allChildrenUsed = true;
        if (!p.children.empty()) {
            for (const string& child : p.children) {
                if (!inOrder(child, curOrder)) {
                    allChildrenUsed = false;
                    break;
                }
            }
        }

        if (p.children.empty() || allChildrenUsed) {
            // поднимаемся к родителю
            if (p.kingStatus) {
                // у корня родителя нет, больше никого
                return "";
            } else {
                return Successor(p.parent, curOrder);
            }
        } else {
            // ищем самого старшего ребёнка, который ещё не в curOrder
            for (const string& child : p.children) {
                if (!inOrder(child, curOrder)) {
                    return child;
                }
            }
            // сюда ход не должен доходить из-за проверки выше,
            // но на всякий случай возвращаем пустую строку
            return "";
        }
    }

public:
    // 1. Конструктор: создаёт короля и инициализирует структуру
    ThroneInheritance(const string& kingName_) : kingName(kingName_) {
        if (!name_ok(kingName_)) {
            throw out_of_range("Превышена длина имени короля.");
        }
        Person king;
        king.kingStatus = true;
        king.parent = "";
        people[kingName_] = king;
    }

    // 2. Рождение ребёнка
    void birth(const string& parentName, const string& childName) {
        if (!name_ok(parentName) || !name_ok(childName)) {
            throw out_of_range("Превышена длина имени.");
        }

        auto it = people.find(parentName);
        if (it == people.end()) {
            throw invalid_argument("Не найден родитель.");
        }

        Person child;
        child.parent = parentName;
        people[childName] = child;

        // ребёнок добавляется в конец списка детей
        it->second.children.push_back(childName);
    }

    // 3. Смерть человека
    void death(const string& deadName) {
        auto it = people.find(deadName);
        if (it == people.end()) {
            throw invalid_argument("Не найдено имя умершего.");
        }
        // порядок наследования не меняется,
        // только пометка, что человек не входит в выдачу
        it->second.aliveStatus = false;
    }

    // 4. Текущий порядок наследования
    vector<string> getInheritanceOrder() const {
        vector<string> rawOrder;   // порядок по Successor, без учёта смерти
        vector<string> result;     // итоговый список только живых

        // стартуем с короля
        rawOrder.push_back(kingName);

        // последовательно вызываем Successor, пока не вернёт пустую строку
        string current = kingName;
        while (true) {
            string next = Successor(current, rawOrder);
            if (next.empty()) break;
            rawOrder.push_back(next);
            current = next;
        }

        // теперь фильтрация: в ответ включаются только живые
        for (const string& name : rawOrder) {
            auto it = people.find(name);
            if (it != people.end() && it->second.aliveStatus) {
                result.push_back(name);
            }
        }

        return result;
    }
};

int main() {
    try {
        ThroneInheritance t("king");   // order: king

        t.birth("king", "andy");       // king > andy
        t.birth("king", "bob");        // king > andy > bob
        t.birth("king", "catherine");  // king > andy > bob > catherine
        t.birth("andy", "matthew");    // king > andy > matthew > bob > catherine
        t.birth("bob", "alex");        // king > andy > matthew > bob > alex > catherine
        t.birth("bob", "asha");        // king > andy > matthew > bob > alex > asha > catherine

        cout << t.getInheritanceOrder() << endl;
        // ожидается: king andy matthew bob alex asha catherine

        t.death("bob");

        cout << t.getInheritanceOrder() << endl;
        // ожидается: king andy matthew alex asha catherine
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
