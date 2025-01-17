#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT)
public:
    static constexpr size_t defaultBoardDimension {4};
    GameBoard(const size_t m_dimension = defaultBoardDimension, QObject* parent = nullptr);

    struct Tile
    {
        size_t value;
        Tile& operator =(const size_t newValue)
        {
            value = newValue;
            return *this;
        }
        bool operator ==(const size_t other)
        {
            return other == value;
        }
    };

    // Чтобы класс перестал быть абстрактным надо переопределить метод:
    int rowCount(const QModelIndex& parent = QModelIndex {} ) const override;

    // Для общения c++ и QML метод data()
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


    size_t dimension() const;
    size_t boardSize() const;

    // Ход фишкой при клике
    Q_INVOKABLE bool move(int index); // Q_INVOKABLE  чтобы вызывать из qml
    using Position = std::pair<size_t,size_t>;
    Position getRowCol(const size_t index);


private:
    std::vector<Tile> m_rawBoard;
    // Чтобы делать доску разных размеров: 5х5 или 6х6
    const size_t m_dimension;
    const size_t m_boardSize;
    void Shuffle();
    bool isPositionValid(const size_t position) const;
};

#endif // GAMEBOARD_H
