class Vector2{
    public:
        Vector2();
        Vector2(auto x, auto y);
}
class Map{
    public:
        Map(int w, int h);
        Map(Vector2 size);

        void SetCurrentCell(Vector2 cord);
        setDirection(int rot); //deg
        Vector2 NextCell(); //return the cell that need to go next
}