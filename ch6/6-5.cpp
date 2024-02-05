#include <cstdio>
#include <iostream>
#include <unordered_map>

// Using the example from Chapter 5, make Bank a template class that
// accepts a template parameter. Use this type parameter as the type of an
// account rather than long. Verify that your code still works using a
// Bank<long> class.

struct Logger {
  virtual void log_transfer(long from, long to, long amount) = 0;
  virtual ~Logger() = default;
};

struct ConsoleLogger : Logger {
  ConsoleLogger(const char *prefix) : prefix{prefix} {}
  void log_transfer(long from, long to, long amount) override {
    printf("%s Transfer from %ld to %ld: %ld\n", prefix, from, to, amount);
  }

private:
  const char *prefix;
};

struct FileLogger : Logger {
  void log_transfer(long from, long to, long amount) override {
    printf("[file] Transfer from %ld to %ld: %ld\n", from, to, amount);
  }
};

template <typename AccountT> struct AccountDatabase {
  virtual void transfer(AccountT from, AccountT to, long amount) = 0;
  virtual void print_accounts_data() = 0;
  virtual ~AccountDatabase() = default;
};

template <typename AccountT>
struct InMemoryAccountDatabase : AccountDatabase<AccountT> {
  void transfer(AccountT from, AccountT to, long amount) override {
    if (accounts_data.contains(to)) {
      accounts_data[to] += amount;
    } else {
      accounts_data[to] = amount;
    }
    if (accounts_data.contains(from)) {
      accounts_data[from] -= amount;
    } else {
      accounts_data[from] = -amount;
    }
  }

  void print_accounts_data() override {
    for (const auto &[account, balance] : accounts_data) {
      std::cout << "Account: " << account << ", Balance: " << balance
                << std::endl;
    }
  }

private:
  std::unordered_map<AccountT, long> accounts_data; //needs hash implementation
};

template <typename AccountT> struct Bank {
  Bank(Logger *logger, AccountDatabase<AccountT> &database)
      : database{database}, logger(logger) {}
  void set_logger(Logger *logger) { this->logger = logger; }

  void print_accounts_data() { database.print_accounts_data(); }

  void make_transfer(AccountT from, AccountT to, long amount) {
    database.transfer(from, to, amount);
    logger->log_transfer(from, to, amount);
  }

private:
  AccountDatabase<AccountT> &database;
  Logger *logger;
};

int main() {
  ConsoleLogger cl("[console_prefix]");
  InMemoryAccountDatabase<long> db;
  FileLogger fl;
  Bank<long> bank(&cl, db);
  bank.make_transfer(1, 2, 100);
  bank.make_transfer(3, 4, 200);
  bank.set_logger(&fl);
  bank.make_transfer(5, 6, 300);
  bank.make_transfer(7, 8, 400);
  bank.print_accounts_data();
  return 0;
}