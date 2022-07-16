#ifndef FINAL_PROJ_WORDLE_INTERFACE_HPP_
#define FINAL_PROJ_WORDLE_INTERFACE_HPP_

#include <QTextStream>

namespace Runge::WordleInterface::privateDetails {
class ISerializable {
public:
  virtual QTextStream &operator<<(QTextStream &) = 0;
  virtual QString to_string() = 0;
};

class IDeserializable {
public:
  virtual QTextStream &operator>>(QTextStream &) = 0;
  virtual IDeserializable &from_string(const QString &) = 0;
};

class ISwappable {
public:
  virtual void swap(ISwappable &) = 0;
};

class INoncopyable {
private:
  INoncopyable(const INoncopyable &) = delete;
  INoncopyable &operator=(const INoncopyable &) = delete;
};

class IComparable {
public:
  virtual bool operator==(const IComparable &) = 0;
};

class IWordle : public IComparable,
                public ISerializable,
                public IDeserializable {
  virtual ~IWordle() = 0;
};

class ICorrectTestable {
public:
  virtual ~ICorrectTestable() = 0;
  virtual bool is_correct_wordle() = 0;
};

class IComparedWordle : public ICorrectTestable,
                        public ISerializable,
                        public IComparable {
  virtual ~IComparedWordle() = 0;
};

class IGenerateCallable {
public:
  virtual ~IGenerateCallable() = 0;
  virtual IWordle generate() = 0;
};

class IValidTestable {
public:
  virtual ~IValidTestable() = 0;
  virtual bool is_valid_wordle(const IWordle &) = 0;
};

class ICompareCallable {
public:
  virtual ~ICompareCallable() = 0;
  virtual IComparedWordle compare(const IWordle &, const IWordle &) = 0;
};

class IWordleComparator : public ICompareCallable, public INoncopyable {
public:
  virtual ~IWordleComparator() = 0;
};

class IWordleGenerator : public IValidTestable,
                         public IGenerateCallable,
                         public INoncopyable {
public:
  virtual ~IWordleGenerator() = 0;
};

}; // namespace Runge::WordleInterface::privateDetails

namespace Runge::WordleInterface {
using privateDetails::IComparedWordle;
using privateDetails::IWordle;
using privateDetails::IWordleComparator;
using privateDetails::IWordleGenerator;
}; // namespace Runge::WordleInterface

#endif
