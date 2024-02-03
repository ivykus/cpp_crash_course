#include <cstdio>
#include <iostream>
#include <unordered_map>

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

struct AccountDatabase {
  virtual void transfer(long from, long to, long amount) = 0;
  virtual void print_accounts_data() = 0;
  virtual ~AccountDatabase() = default;
};

struct InMemoryAccountDatabase : AccountDatabase {
  void transfer(long from, long to, long amount) override {
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
  std::unordered_map<long, long> accounts_data;
};

struct Bank {
  Bank(Logger *logger, AccountDatabase &database)
      : database{database}, logger(logger) {}
  void set_logger(Logger *logger) { this->logger = logger; }

  void print_accounts_data() { database.print_accounts_data(); }

  void make_transfer(long from, long to, long amount) {
    database.transfer(from, to, amount);
    logger->log_transfer(from, to, amount);
  }

private:
  AccountDatabase &database;
  Logger *logger;
};

int main() {
  ConsoleLogger cl("[console_prefix]");
  InMemoryAccountDatabase db;
  FileLogger fl;
  Bank bank(&cl, db);
  bank.make_transfer(1, 2, 100);
  bank.make_transfer(3, 4, 200);
  bank.set_logger(&fl);
  bank.make_transfer(5, 6, 300);
  bank.make_transfer(7, 8, 400);
  bank.print_accounts_data();
  return 0;
}
