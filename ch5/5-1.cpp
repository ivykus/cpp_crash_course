#include <cstdio>

struct Logger {
  virtual void log_transfer(long from, long to, long amount) = 0;
  virtual ~Logger() = default;
};

struct ConsoleLogger : Logger {
  void log_transfer(long from, long to, long amount) override {
    printf("[console] Transfer from %ld to %ld: %ld\n", from, to, amount);
  }
};

struct FileLogger : Logger {
  void log_transfer(long from, long to, long amount) override {
    printf("[file] Transfer from %ld to %ld: %ld\n", from, to, amount);
  }
};

struct AccountDatabase {
  virtual void transfer(long from, long to, long amount) = 0;
  virtual ~AccountDatabase() = default;
};

struct Bank {
  Bank(Logger *logger) : logger(logger) {}
  void set_logger(Logger *logger) { this->logger = logger; }

  void make_transfer(long from, long to, long amount) {
    logger->log_transfer(from, to, amount);
  }

private:
  Logger *logger;
};

int main() {
  ConsoleLogger cl;
  FileLogger fl;
  Bank bank(&cl);
  bank.make_transfer(1, 2, 100);
  bank.make_transfer(3, 4, 200);
  bank.set_logger(&fl);
  bank.make_transfer(5, 6, 300);
  bank.make_transfer(7, 8, 400);
  return 0;
}
