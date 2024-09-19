/* 1. Принцип подстановки Лисков
 В классах, наследующих от Printable, нарушается контракт интерфейса.Например, в классе Data каждый метод форматирования ограничен проверкой конкретного формата.
 Это приводит к тому, что объект, который должен поддерживать все форматы, может бросать исключения, если вызывается неправильный метод для текущего формата b потомок не может корректно заменить базовый класс везде, где он используется.

 2. Принцип открытости/закрытости
 При добавлении новых форматов данных нам нужно будет изменять существующий класс Data, добавляя новые условия для каждого формата.

 3. Принцип разделения интерфейсов
  Интерфейс Printable включает в себя методы для вывода в текст, HTML и JSON, заставляя всех наследников реализовывать все эти методы.
  Это нарушает принцип разделения интерфейсов, так как не каждому классу нужны все три метода.
*/

#include <fstream>
#include <string>
#include <stdexcept>

// Интерфейсы для каждого формата
class PrintableText
{
public:
    virtual ~PrintableText() = default;
    virtual std::string printAsText() const = 0;
};

class PrintableHTML
{
public:
    virtual ~PrintableHTML() = default;
    virtual std::string printAsHTML() const = 0;
};

class PrintableJSON
{
public:
    virtual ~PrintableJSON() = default;
    virtual std::string printAsJSON() const = 0;
};

// Базовый класс для данных
class Data
{
public:
    explicit Data(std::string data) : data_(std::move(data)) {}
    virtual ~Data() = default;

protected:
    std::string data_;
};

// Классы для каждого формата данных
class TextData : public Data, public PrintableText
{
public:
    explicit TextData(const std::string& data) : Data(data) {}

    std::string printAsText() const override
    {
        return data_;
    }
};

class HTMLData : public Data, public PrintableHTML
{
public:
    explicit HTMLData(const std::string& data) : Data(data) {}

    std::string printAsHTML() const override
    {
        return "<html>" + data_ + "<html/>";
    }
};

class JSONData : public Data, public PrintableJSON
{
public:
    explicit JSONData(const std::string& data) : Data(data) {}

    std::string printAsJSON() const override
    {
        return "{ \"data\": \"" + data_ + "\" }";
    }
};

// Функции сохранения данных
void saveToAsText(std::ofstream& file, const PrintableText& printable)
{
    file << printable.printAsText();
}

void saveToAsHTML(std::ofstream& file, const PrintableHTML& printable)
{
    file << printable.printAsHTML();
}

void saveToAsJSON(std::ofstream& file, const PrintableJSON& printable)
{
    file << printable.printAsJSON();
}

int main()
{
    std::ofstream file("output.txt");

    // Пример использования
    TextData textData("This is plain text");
    saveToAsText(file, textData);

    HTMLData htmlData("This is HTML content");
    saveToAsHTML(file, htmlData);

    JSONData jsonData("This is JSON content");
    saveToAsJSON(file, jsonData);

    return 0;
}
