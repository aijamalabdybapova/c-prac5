#include <iostream>
#include <Windows.h>

using namespace std;

class BankAccount {
    private:
        int accountNumber;
        double balance;
        double interestRate;

    public:
        // Конструктор
        BankAccount(int accountNumber, double balance, double interestRate) : accountNumber(accountNumber), balance(balance), interestRate(interestRate) {}

        // Внести средства на счет
        void deposit(double amount) {
            if (amount <= 0) {
                throw invalid_argument("Сумма депозита должна быть положительной");
            }
            balance += amount;
        }

        // Снять средства со счета
        void withdraw(double amount) {
            if (amount <= 0) {
                throw invalid_argument("Сумма снятия должна быть положительной");
            }
            if (amount > balance) {
                throw invalid_argument("Недостаточно средств на счете");
            }
            balance -= amount;
        }

        // Получить баланс
        double getBalance() const {
            return balance;
        }

        // Рассчитать и вернуть сумму процентов
        double getInterest() const {
            return balance * interestRate * (1.0 / 12.0);
        }

        // Обновить процентную ставку
        void setInterestRate(double newInterestRate) {
            if (newInterestRate < 0.0 || newInterestRate > 1.0) {
                throw invalid_argument("Процентная ставка должна быть в пределах от 0,0 до 1,0");
            }
            interestRate = newInterestRate;
        }

        // Получить номер счета
        int getAccountNumber() const {
            return accountNumber;
        }

        // Дружественная функция для перевода средств
        friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

// Дружественная функция для перевода средств
bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount <= 0) {
        throw invalid_argument("Сумма перевода должна быть положительной");
    }
    if (amount > from.balance) {
        return false;
    }
    from.withdraw(amount);
    to.deposit(amount);
    return true;
}

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    try {
        // Создать два банковских счета
        BankAccount account1(123456, 1000.0, 0.05);
        BankAccount account2(654321, 2000.0, 0.07);

        // Внести 500 долларов на первый счет
        account1.deposit(500.0);

        // Снять 300 долларов со второго счета
        account2.withdraw(300.0);

        // Рассчитать и вывести проценты по первому счету
        cout << "Проценты по первому счету: " << account1.getInterest() << endl;

        // Перевести 200 долларов со второго счета на первый счет
        if (transfer(account2, account1, 200.0)) {
            cout << "Перевод успешен" << endl;
        } else {
            cout << "Перевод не удался" << endl;
        }

        // Вывести балансы обоих счетов
        cout << "Баланс первого счета: " << account1.getBalance() << endl;
        cout << "Баланс второго счета: " << account2.getBalance() << endl;
    } catch (invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}