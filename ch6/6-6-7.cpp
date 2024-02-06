#include <concepts>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

// 6-6. Implement an Account class and instantiate a Bank<Account>. Implement
// functions in Account to keep track of balances

// 6-7. Make Account an interface. Implement a CheckingAccount and
// SavingsAccount. Create a program with several checking and savings
// accounts. Use a Bank<Account> to make several transactions between
// the accounts.

struct Account {
  virtual void deposit(long amount) { balance += amount; }
  virtual void withdraw(long amount) { balance -= amount; }
  virtual long getBalance() { return balance; }
  virtual ~Account() = default;
  virtual std::string getID() = 0;
  virtual void printInfo() = 0;

protected:
  long balance;
};

struct CheckingAccount final : Account {
  CheckingAccount(long amount) {
    id = id_generator++;
    balance = amount;
  }

  std::string getID() override {
    return std::string("CheckingAccount-") + std::to_string(id);
  }

  virtual void printInfo() override {
    std::cout << getID() << " Balance: " << getBalance() << std::endl;
  }

private:
  static long id_generator;
  long id;
};

struct SavingsAccount final : Account {
  SavingsAccount(long balance_) {
    id = id_generator++;
    balance = balance_;
  }

  std::string getID() override {
    return std::string("SavingsAccount-") + std::to_string(id);
  }

  void printInfo() override {
    std::cout << getID() << " Balance: " << getBalance() << std::endl;
  }

private:
  long id;
  static long id_generator;
};

template <typename AccountT>
  requires std::derived_from<Account, Account>
struct Bank {

  void make_transfer(AccountT &from, AccountT &to, long amount) {
    from.withdraw(amount);
    to.deposit(amount);
    std::cout << "Transfer from " << from.getID() << " to " << to.getID()
              << " amount " << amount << std::endl;
  }
};

long CheckingAccount::id_generator = 0;
long SavingsAccount::id_generator = 0;

int main() {
  Bank<Account> bank{};
  CheckingAccount ca{100};
  SavingsAccount sa{100};
  bank.make_transfer(ca, sa, 100);
  CheckingAccount sb{500};
  bank.make_transfer(sb, sa, 200);
  ca.printInfo();
  sa.printInfo();
  sb.printInfo();
  return 0;
}