#include <iostream>
#include <vector>

using namespace std;

// Константы максимального возраста (можно подправить под свои хотелки)
const int MAX_AGE_PREY     = 15;
const int MAX_AGE_PREDATOR = 20;

// Направления: 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
// dx, dy считаем по x (столбец, 0..N-1) и y (строка, 0..M-1)
int dx[4] = { 0,  1,  0, -1};
int dy[4] = {-1,  0,  1,  0};

int wrapCoord(int value, int maxDim) {
    value %= maxDim;
    if (value < 0) value += maxDim;
    return value;
}

// Базовый класс "зверь"
class Animal {
protected:
    int x;              // координата по X (столбец)
    int y;              // координата по Y (строка)
    int dir;            // направление (0..3)
    int k;              // период смены направления
    int age;            // возраст
    bool alive;         // жив ли зверь
    int stepsSinceTurn; // сколько ходов прошло с последней смены направления

    // Общий код движения, шаг задаёт потомок
    void moveWithStep(int step, int N, int M) {
        if (!alive) return;
        x = wrapCoord(x + dx[dir] * step, N);
        y = wrapCoord(y + dy[dir] * step, M);
        stepsSinceTurn++;
        if (k > 0 && (stepsSinceTurn % k == 0)) {
            dir = (dir + 1) % 4; // смена направления по часовой стрелке
        }
    }

public:
    Animal(int x, int y, int dir, int k)
        : x(x), y(y), dir(dir), k(k),
          age(0), alive(true), stepsSinceTurn(0) {}

    virtual ~Animal() = default;

    // Чисто виртуальные методы (полиморфизм)
    virtual void move(int N, int M) = 0;          // движение
    virtual bool isPredator() const = 0;          // хищник/жертва
    virtual void eat(int preyCount) = 0;          // "поесть" (для хищника)
    virtual Animal* maybeReproduce() = 0;         // размножение (0 или новый зверь)
    virtual int getMaxAge() const = 0;            // максимум возраста

    // Общее поведение
    void die()               { alive = false; }
    bool isAlive() const     { return alive; }
    void incrementAge()      { if (alive) ++age; }
    int  getAge() const      { return age; }
    int  getX() const        { return x; }
    int  getY() const        { return y; }
    int  getDir() const      { return dir; }
    int  getK() const        { return k; }
};

// Жертва (например, заяц)
class Prey : public Animal {
    bool reproducedAt5;
    bool reproducedAt10;
public:
    Prey(int x, int y, int dir, int k)
        : Animal(x, y, dir, k),
          reproducedAt5(false),
          reproducedAt10(false) {}

    void move(int N, int M) override {
        // Жертва ходит на 1 клетку
        moveWithStep(1, N, M);
    }

    bool isPredator() const override {
        return false;
    }

    void eat(int /*preyCount*/) override {
        // Жертвы никого не едят
    }

    // Размножение: два раза за жизнь – в возрасте 5 и 10
    Animal* maybeReproduce() override {
        if (!alive) return nullptr;
        bool shouldReproduce = false;

        if (age >= 5 && !reproducedAt5) {
            reproducedAt5 = true;
            shouldReproduce = true;
        }
        if (age >= 10 && !reproducedAt10) {
            reproducedAt10 = true;
            shouldReproduce = true;
        }

        if (shouldReproduce) {
            // Ребёнок с теми же направлением и k, возраст 0
            return new Prey(x, y, dir, k);
        }
        return nullptr;
    }

    int getMaxAge() const override {
        return MAX_AGE_PREY;
    }
};

// Хищник (например, волк)
class Predator : public Animal {
    int eatenPrey; // сколько жертв съел с рождения (для размножения)
public:
    Predator(int x, int y, int dir, int k)
        : Animal(x, y, dir, k),
          eatenPrey(0) {}

    void move(int N, int M) override {
        // Хищник ходит на 2 клетки
        moveWithStep(2, N, M);
    }

    bool isPredator() const override {
        return true;
    }

    // Хищник съел preyCount жертв
    void eat(int preyCount) override {
        if (!alive) return;
        eatenPrey += preyCount;
    }

    // Размножение: за каждые 2 съеденных жертвы рождается 1 новый хищник
    Animal* maybeReproduce() override {
        if (!alive) return nullptr;
        if (eatenPrey >= 2) {
            eatenPrey -= 2;
            return new Predator(x, y, dir, k);
        }
        return nullptr;
    }

    int getMaxAge() const override {
        return MAX_AGE_PREDATOR;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, T;
    if (!(cin >> N >> M >> T)) {
        return 0;
    }

    int R, W;
    cin >> R >> W;

    vector<Animal*> animals;
    animals.reserve(R + W + 1000);

    // Читаем жертв
    for (int i = 0; i < R; ++i) {
        int x, y, d, k;
        cin >> x >> y >> d >> k;
        animals.push_back(new Prey(x, y, d, k));
    }

    // Читаем хищников
    for (int i = 0; i < W; ++i) {
        int x, y, d, k;
        cin >> x >> y >> d >> k;
        animals.push_back(new Predator(x, y, d, k));
    }

    // Основной цикл по ходам
    for (int step = 0; step < T; ++step) {
        // 1) Движение
        for (auto a : animals) {
            if (a->isAlive()) {
                a->move(N, M);
            }
        }

        // 2) Питание
        // Заполним клетки индексами зверей
        vector<vector<vector<int>>> cells(M, vector<vector<int>>(N));
        for (int i = 0; i < (int)animals.size(); ++i) {
            Animal* a = animals[i];
            if (!a->isAlive()) continue;
            int x = a->getX();
            int y = a->getY();
            cells[y][x].push_back(i);
        }

        // Для каждой клетки смотрим, есть ли там и хищники, и жертвы
        for (int y = 0; y < M; ++y) {
            for (int x = 0; x < N; ++x) {
                auto& v = cells[y][x];
                if (v.size() <= 1) continue;

                int preyCount = 0;
                int firstPredIndex = -1;

                // Считаем, кто там
                for (int idx : v) {
                    Animal* a = animals[idx];
                    if (!a->isAlive()) continue;
                    if (a->isPredator()) {
                        if (firstPredIndex == -1)
                            firstPredIndex = idx;
                    } else {
                        preyCount++;
                    }
                }

                if (preyCount > 0 && firstPredIndex != -1) {
                    // Первый хищник съедает всех жертв
                    Predator* pred = dynamic_cast<Predator*>(animals[firstPredIndex]);
                    if (pred) {
                        pred->eat(preyCount);
                    }
                    // Все жертвы умирают
                    for (int idx : v) {
                        Animal* a = animals[idx];
                        if (!a->isAlive()) continue;
                        if (!a->isPredator()) {
                            a->die();
                        }
                    }
                }
            }
        }

        // 3) Старение
        for (auto a : animals) {
            if (a->isAlive()) {
                a->incrementAge();
            }
        }

        // 4) Размножение
        vector<Animal*> newborns;
        // Важно: размножаем только по "старым" зверям, не по новорождённым этого же шага
        int currentSize = (int)animals.size();
        for (int i = 0; i < currentSize; ++i) {
            Animal* a = animals[i];
            if (!a->isAlive()) continue;
            // Возможно несколько рождений (у хищников, если съели 4,6,... жертв)
            while (true) {
                Animal* child = a->maybeReproduce();
                if (!child) break;
                newborns.push_back(child);
            }
        }
        for (auto child : newborns) {
            animals.push_back(child);
        }

        // 5) Вымирание (по возрасту)
        for (auto a : animals) {
            if (a->isAlive() && a->getAge() >= a->getMaxAge()) {
                a->die();
            }
        }
    }

    // После T ходов формируем поле
    vector<vector<int>> preyCount(M, vector<int>(N, 0));
    vector<vector<int>> predCount(M, vector<int>(N, 0));

    for (auto a : animals) {
        if (!a->isAlive()) continue;
        int x = a->getX();
        int y = a->getY();
        if (a->isPredator()) {
            predCount[y][x]++;
        } else {
            preyCount[y][x]++;
        }
    }

    // Вывод M строк по N символов / токенов
    for (int y = 0; y < M; ++y) {
        for (int x = 0; x < N; ++x) {
            int pc = preyCount[y][x];
            int hc = predCount[y][x];
            if (pc == 0 && hc == 0) {
                cout << '*';
            } else if (pc > 0 && hc == 0) {
                cout << '+' << pc;
            } else if (hc > 0 && pc == 0) {
                cout << '-' << hc;
            } else {
                // Теоретически не должно случаться к концу хода,
                // но на всякий случай выведем приоритет хищников
                cout << '-' << hc;
            }
        }
        cout << "\n";
    }

    // Освобождаем память
    for (auto a : animals) {
        delete a;
    }

    return 0;
}
