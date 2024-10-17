/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class Character;
class Robot;
class RobotS;
class RobotW;
class RobotSW;
 class RobotC;

class ArrayMovingObject;
 class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag; 
class MagicBook;
class FirstAid;
class EnergyDrink;
class ExcemptionCard;
class PassingCard;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

    

class MapElement{
    protected:
    ElementType type;

    public:
    MapElement(){}
    MapElement(ElementType in_type){
        this->type = in_type;
    }

    void setType(ElementType type){
        this->type = type;
    }
    virtual ~MapElement(){};
    virtual ElementType getType () const{
        return type;
    }

    friend class TestStudyInPink;
};

class Path : public MapElement{
    public:
    Path() : MapElement(PATH){   
    }
    
    ElementType getType() const{
        return PATH;
    }
    friend class TestStudyInPink;
};

class Wall : public MapElement {
    public:
    Wall() : MapElement(WALL){}

    ElementType getType() const{
        return WALL;
    }
    friend class TestStudyInPink;
};

class FakeWall : public MapElement {
    private:
    int req_exp;

    public:

    FakeWall() : MapElement(FAKE_WALL){}

    FakeWall(int in_req_exp){

        req_exp = in_req_exp;
    }

    int getReqExp () const {
        return req_exp;

    }

    ElementType getType() const{
        return FAKE_WALL;
    }
    friend class TestStudyInPink;
};

class Position {
private:
    int r, c;
public:
    

    Position (){
        r = 0;
        c = 0;
    }

    Position(int r){
        this->r = r;
        c = 0;
    }

    Position(int r, int c){
        this->r = r;
        this->c = c;
    }

    Position( const string & str_pos ){
        size_t moc_truoc = str_pos.find("(");
        size_t moc_sau = str_pos.find(")");
        size_t dauphay = str_pos.find(",");

        this->r = stoi(str_pos.substr(moc_truoc + 1, dauphay));
        this->c = stoi(str_pos.substr(dauphay + 1, moc_sau));
        
    }

    void stposition(const string & str_pos){
        size_t moc_truoc = str_pos.find("(");
        size_t moc_sau = str_pos.find(")");
        size_t dauphay = str_pos.find(",");
        if(moc_truoc + 1 == dauphay) this->r = 0;
        else this->r = stoi(str_pos.substr(moc_truoc + 1, dauphay));
        if(dauphay + 1 == moc_sau) this->c = 0;
        else this->c = stoi(str_pos.substr(dauphay + 1, moc_sau));

    }

    int getRow() const{
        return r;
    }

    int getCol() const{
        return c;
    }

    void setRow (int r){
        this->r = r;
    }

    void setCol (int c){
        this->c = c;
    }


    string str() const{
        string s;
        s +='(';
        s+= to_string(this->r);
        s+=",";
        s+= to_string(this->c);
        s+=')';
        return s;
    }

    

    bool isEqual (int in_r , int in_c ) const{
        if(r == in_r && c == in_c) return true;
        else return false;
    }

    bool isEqual (Position pos) const{
        if(this->r == pos.getRow() && this->c == pos.getCol()) return true;
        else return false;
    }

    int get_distance(Position draft_pos){
        return abs(r - draft_pos.getRow()) + abs(c - draft_pos.getCol());
    }
    friend class TestStudyInPink;
};

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;
    int hp;
    int exp;

public:
    MovingObject(){}

    MovingObject (int index , const Position pos , Map * map){
        this->index = index;
        this->pos = pos;
        this->map = map;
        this->name = " ";
    }

    virtual ~MovingObject(){}
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const{
        return this->pos;
    }
    virtual void move() = 0;
    virtual string str() const = 0;

    string getName(){
        return name;
    }

    int getExp(){
        return exp;
    }

    int getHp(){
        return hp;
    }

    int getIndex(){
        return index;
    }

    void setPos(Position pos){
        this->pos = pos;
    }
    void setExp(int exp){
        if(exp>900) exp = 900;
        else if(exp < 0) exp = 0;
        this->exp = exp;
    }

    void setHp(int hp){
        if(hp>500) hp = 500;
        else if(hp < 0) hp = 0;
        this->hp = hp;
    }

    virtual BaseItem * getItem() = 0;
    friend class TestStudyInPink;
};

class Map {
private:
    int num_rows, num_cols;
    int num_walls;
    Position * array_walls;
    int num_fake_walls;
    Position *array_fake_walls;
    
    MapElement*** map = new MapElement**[this->num_rows];

public:

    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) : num_rows(num_rows), num_cols(num_cols){
        this->num_rows = num_rows ;
        this->num_cols = num_cols ;
        this->num_walls = num_walls;
        this->array_walls = array_walls;
        this-> num_fake_walls = num_fake_walls;
        this-> array_fake_walls = array_fake_walls;

        for (int i = 0; i < this->num_rows; i++){
        map[i] = new MapElement*[this->num_cols];
        }

        for(int i = 0; i < this->num_rows; i++){
            for(int j = 0;  j < this->num_cols; j++){
                int xemxet = 0;
                for(int k = 0; k < num_walls; k++){
                    if(i == array_walls[k].getRow() && j == array_walls[k].getCol()){
                        map[i][j] = new Wall();
                        xemxet = 1;
                        break;
                    }
                }
                if(xemxet == 0){
                    for(int m = 0; m < num_fake_walls; m++){
                    if(i == array_fake_walls[m].getRow() && j == array_fake_walls[m].getCol()){
                        map[i][j] = new FakeWall((array_fake_walls[m].getRow() * 257 + array_fake_walls[m].getCol() * 139 + 89) % 900 + 1);
                        xemxet = 1;
                        break;
                    }
                }
                }

                if(xemxet == 0){
                    map[i][j] = new Path();
                }
                
            }
        }
    }

    void setMap(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls){
        this->num_rows = num_rows ;
        this->num_cols = num_cols ;
        this->num_walls = num_walls;
        this->array_walls = array_walls;
        this-> num_fake_walls = num_fake_walls;
        this-> array_fake_walls = array_fake_walls;

        for (int i = 0; i < this->num_rows; i++){
        map[i] = new MapElement*[this->num_cols];
        }

        for(int i = 0; i < this->num_rows; i++){
            for(int j = 0;  j < this->num_cols; j++){
                int xemxet = 0;
                for(int k = 0; k < num_walls; k++){
                    if(i == array_walls[k].getRow() && j == array_walls[k].getCol()){
                        map[i][j] = new Wall();
                        xemxet = 1;
                        break;
                    }
                }
                if(xemxet == 0){
                    for(int m = 0; m < num_fake_walls; m++){
                    if(i == array_fake_walls[m].getRow() && j == array_fake_walls[m].getCol()){
                        map[i][j] = new FakeWall((array_fake_walls[m].getRow() * 257 + array_fake_walls[m].getCol() * 139 + 89) % 900 + 1);
                        xemxet = 1;
                        break;
                    }
                }
                }

                if(xemxet == 0){
                    map[i][j] = new Path();
                }
                
            }
        }
    }

    ~Map(){
    for (int i = 0; i < this->num_rows; i++){
        for(int j = 0; j > this->num_cols; j++){
            delete map[i][j];
        }
        delete [] map[i];
    }
        
        delete [] this->map;
        
    }
    
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const{
        if(pos.getRow() < 0 || pos.getCol() < 0 || pos.getRow() >= num_rows || pos.getCol() >= num_cols ) return false;
        if(map[pos.getRow()][pos.getCol()]->getType() == PATH){
            return true; 
        }
        else if(mv_obj->getName() == "Sherlock"){
            if(map[pos.getRow()][pos.getCol()]->getType() == FAKE_WALL){
            return true; 
            }
        }
        else if(mv_obj->getName() == "Watson"){
            if(map[pos.getRow()][pos.getCol()]->getType() == FAKE_WALL){  
                int draft_exp = ((pos.getRow() * 257 + pos.getCol() * 139 + 89) % 900 + 1);    
                if( draft_exp < mv_obj->getExp()) return true;
            }
        }
        return false;
    }

    friend class TestStudyInPink;
};

static const Position npos(-1, -1);



class Character : public MovingObject{
    
    public:
    Character(){}
    Character(int index){
        this->index = index;
    }

    Position getNextPosition(){
        return npos;
    }
    void move(){}
    string str() const{
        return "";
    }

    BaseItem * getItem(){
        return NULL;
    }
    
    friend class TestStudyInPink;
};

class Sherlock : public Character{
    public:
    string moving_rule;

    
    
    Sherlock(){
        this->name = "Sherlock";
    }

    Sherlock ( int index , const string & moving_rule , const Position &init_pos , Map * map , int hp , int exp ): Character(index) {
        this->pos = init_pos;
        this->map = map;
        this->moving_rule = moving_rule;
        this->hp = hp;
        this->exp = exp;
        this->name = "Sherlock";
      

        if(hp>500) hp = 500;
        else if(hp < 0) hp = 0;

        if(exp>900) exp = 900;
        else if(exp < 0) exp = 0;
    }

    int thutu_sherlock = 0;

    Position getNextPosition(){

        Position draft_pos = pos;
        
        if(moving_rule[thutu_sherlock] == 'U' ) draft_pos.setRow(draft_pos.getRow()-1);
        else if(moving_rule[thutu_sherlock] == 'D' ) draft_pos.setRow(draft_pos.getRow()+1);
        else if(moving_rule[thutu_sherlock] == 'R' ) draft_pos.setCol(draft_pos.getCol()+1);
        else if(moving_rule[thutu_sherlock] == 'L' ) draft_pos.setCol(draft_pos.getCol()-1);
        thutu_sherlock++;
        int draft_length = moving_rule.length();
        if(thutu_sherlock == draft_length ) thutu_sherlock = 0;

        
        if(map->isValid(draft_pos, this )) return draft_pos;
        return npos;
    }

    void move(){
        if(this->getExp() == 0 || this->getHp() == 0);
        else{
            Position draft = this->getNextPosition();
            if(!(draft.isEqual(npos))){
            pos = draft;
            }
        }   
    }

    string str() const{
        string s = "Sherlock[index=";
        s+= to_string(index);
        s+=";pos=";
        s+= pos.str();
        s+=";moving_rule=";
        s+=moving_rule;
        s+="]";
        return s;
    }

    friend class TestStudyInPink;
};

class Watson : public Character{
    public:
    string moving_rule;

    
    
    
    Watson(){
        this->name = "Watson";
    }

    Watson ( int index , const string & moving_rule , const Position &init_pos , Map * map , int hp , int exp ): Character(index){
        this->pos = init_pos;
        this->map = map;
        this->moving_rule = moving_rule;
        this->hp = hp;
        this->exp = exp;
        this->name = "Watson";
        

        if(hp>500) hp = 500;
        else if(hp < 0) hp = 0;

        if(exp>900) exp = 900;
        else if(exp < 0) exp = 0;
    }
    

    int thutu_watson =  0;

    Position getNextPosition(){
        Position draft_pos = pos;
        if(moving_rule[thutu_watson] == 'U' ) draft_pos.setRow(draft_pos.getRow()-1);
        else if(moving_rule[thutu_watson] == 'D' ) draft_pos.setRow(draft_pos.getRow()+1);
        else if(moving_rule[thutu_watson] == 'R' ) draft_pos.setCol(draft_pos.getCol()+1);
        else if(moving_rule[thutu_watson] == 'L' ) draft_pos.setCol(draft_pos.getCol()-1);


        thutu_watson++;
        int draft_length = moving_rule.length();
        if(thutu_watson == draft_length ){
            thutu_watson = 0;
        }
    
        if(map->isValid(draft_pos, this )) return draft_pos;
        return npos;
        
    }

    void move(){
        if(this->getExp() == 0 || this->getHp() == 0);
        else{
            Position draft = this->getNextPosition();
            if(!(draft.isEqual(npos))){
            pos = draft;
            }
        }
        
    }

    string str() const{
        string s = "Watson[index=";
        s+= to_string(index);
        s+=";pos=";
        s+= pos.str();
        s+=";moving_rule=";
        s+=moving_rule;
        s+="]";
        return s;
    }
    friend class TestStudyInPink;
};

class Criminal : public Character{
    public:
    Sherlock *sherlock;
    Watson *watson;
    Position pre_criminal;

    
    Criminal(){
        this->name="Criminal";
    }
    Criminal ( int index , const Position & init_pos , Map * map , Sherlock *sherlock , Watson * watson ): Character(index){
        this->pos = init_pos;
        this->map = map;
        this->sherlock = sherlock;
        this->watson = watson;
        this->name="Criminal";
        this->pre_criminal = npos;
    }


    string str() const{
        string s = "Criminal[index=";
        s+= to_string(index);
        s+=";pos=";
        s+= pos.str();
        s+="]";
        return s;
    }

    Position getNextPosition(){
        Position sherlock_pos = sherlock->getCurrentPosition();
        Position watson_pos = watson->getCurrentPosition();
        int i = -1;
        int max_distance = 0;

        Position draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            max_distance = abs(this->pos.getRow() - 1 - watson_pos.getRow()) + abs(this->pos.getCol()  - watson_pos.getCol()) + abs(this->pos.getRow() - 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol());
            i = 0;
        }
        
        draft_pos = this->pos;
        draft_pos.setCol(this->pos.getCol() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            if(max_distance < abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() - 1  - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol())){
                max_distance = abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() - 1  - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol());
                i = 1;
            }
        }
        
        draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if(max_distance < abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol()) + abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol())){
            max_distance = abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol()) + abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol());
            i = 2;
        }
        }
        
        draft_pos = this->pos;
        draft_pos.setCol(this->pos.getCol() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if(max_distance < abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() + 1  - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol())){
            max_distance = abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() + 1  - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol());
            i = 3;
        }
        }

        draft_pos = this->pos;
        if(i == 0){
            draft_pos.setRow(this->pos.getRow() - 1);
        }
        else if(i == 1){
            draft_pos.setCol(this->pos.getCol() - 1);
        }
        else if(i == 2){
            draft_pos.setRow(this->pos.getRow() + 1);
        }
        else if(i == 3){
            draft_pos.setCol(this->pos.getCol() + 1);
        }
        else if(i == -1){
            return npos;
        }

        return draft_pos;
    }

    void move(){
        Position draft = this->getNextPosition();
        if(!(draft.isEqual(npos))){
            pre_criminal = pos;
            pos = draft;
        }
    }

    Position getPreCri(){
        return pre_criminal;
    }
    friend class TestStudyInPink;
};

class ArrayMovingObject{
    private:
    MovingObject **arr_mv_objs;
    int count = 0;
    int capacity;

    public:
    ArrayMovingObject(){}

    ArrayMovingObject(int capacity){
        this->capacity = capacity;
        arr_mv_objs = new MovingObject*[capacity]; 
    }

    ~ArrayMovingObject(){
        // for(int i = 0; i < capacity; i++){
        //     delete arr_mv_objs[i];
        // }
        delete [] arr_mv_objs;
    }

    bool isFull () const{
        if(count == capacity) return true;
        else return false;
    }

    bool add ( MovingObject * mv_obj ){
        if(this->isFull()) return false;
        else{
            arr_mv_objs[count] = mv_obj;
            count++;
            return true;
        }
    }

    string str() const{
        string s;
        s+= "ArrayMovingObject[count=";
        s+= to_string(count);
        s+=";capacity=";
        s+=to_string(capacity);
        s+=";";
        for(int i = 0; i < count; i++){
            if(i != 0)s+=";";
            s+=arr_mv_objs[i]->str();
        }
        s+="]";
        return s;
    }

    MovingObject * get(int i){
        return arr_mv_objs[i];
    }

    int size(){
        return count;
    }
    friend class TestStudyInPink;
};

class Configuration{
    private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position* arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos; 
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

    public:
    Configuration(){}

    Configuration ( const string & filepath ){

        ifstream file(filepath);
        string line;

        if (!file.is_open()) {
        cout << "File is not opened" << endl;
    }

        while(getline(file, line)){
            size_t moc = line.find("=");
            string sosanh = line.substr(0, moc);
            string value = line.substr(moc + 1);

            if(sosanh == "MAP_NUM_ROWS") map_num_rows = stoi(value);
            else if(sosanh == "MAP_NUM_COLS") map_num_cols = stoi(value);
            else if(sosanh == "MAX_NUM_MOVING_OBJECTS") max_num_moving_objects = stoi(value);
            else if(sosanh == "NUM_WALLS") num_walls = stoi(value);
            else if (sosanh == "ARRAY_WALLS"){
                if( (line.find("(") == string::npos)) num_walls = 0 ;
                else{
                    string draft_line = line;
                arr_walls = new Position[100];
                int j = 0;
                while(true){
                    arr_walls[j].stposition(value);
                    moc = draft_line.find(";");
                    if(moc != string::npos){
                        j++;
                        value = draft_line.substr(moc + 1);
                        draft_line = value;
                    }
                    else{
                        num_walls = j + 1;
                        break;
                    }
                    
                }
                } 
                
            }
            else if(sosanh == "NUM_FAKE_WALLS") num_fake_walls = stoi(value);
            else if(sosanh == "ARRAY_FAKE_WALLS"){
                if((value.find("(") == string::npos)) num_fake_walls = 0;
                else{
                    string draft_line = line;
                arr_fake_walls = new Position[100];
                int j = 0;
                while(true){
                    arr_fake_walls[j].stposition(value);
                    moc = draft_line.find(";");
                    if(moc != string::npos){
                        j++;
                        value = draft_line.substr(moc + 1);
                        draft_line = value;
                    }
                    else{
                        num_fake_walls = j + 1;
                        break;
                    }
                    
                }
                }
                
            }
            else if(sosanh == "SHERLOCK_MOVING_RULE") sherlock_moving_rule = value;
            else if(sosanh == "SHERLOCK_INIT_POS") sherlock_init_pos.stposition(value);
            else if(sosanh == "SHERLOCK_INIT_HP") sherlock_init_hp = stoi(value);
            else if(sosanh == "SHERLOCK_INIT_EXP") sherlock_init_exp = stoi(value);
            else if(sosanh == "WATSON_MOVING_RULE") watson_moving_rule = value;
            else if(sosanh == "WATSON_INIT_POS") watson_init_pos.stposition(value);
            else if(sosanh == "WATSON_INIT_HP") watson_init_hp = stoi(value);
            else if(sosanh == "WATSON_INIT_EXP") watson_init_exp = stoi(value);
            else if(sosanh == "CRIMINAL_INIT_POS") criminal_init_pos.stposition(value);
            else if(sosanh == "NUM_STEPS") num_steps = stoi(value);
          
        }
    }


    ~Configuration(){
        
    }

    string str() const{
        string s;
        s+="Configuration[\n";
        s+="MAP_NUM_ROWS=";
        s+= to_string(map_num_rows);
        s+="\nMAP_NUM_COLS=";
        s+= to_string(map_num_cols);
        s+="\nMAX_NUM_MOVING_OBJECTS=";
        s+= to_string(max_num_moving_objects);
        s+="\nNUM_WALLS=";
        s+= to_string(num_walls);
        s+= "\nARRAY_WALLS=[";
        for(int i = 0; i < num_walls; i++){
            string draft = arr_walls[i].str();
            s+=draft;
            if(i != num_walls - 1) s+=";";
        }
        s+="]";
        s+= "\nNUM_FAKE_WALLS=";
        s+= to_string(num_fake_walls);
        s+= "\nARRAY_FAKE_WALLS=[";
        for(int i = 0; i < num_fake_walls; i++){
            string draft = arr_fake_walls[i].str();
            s+=draft;
            if(i != num_fake_walls - 1) s+=";";
        }
        s+="]";        
        s+= "\nSHERLOCK_MOVING_RULE=";
        s+= sherlock_moving_rule;
        s+= "\nSHERLOCK_INIT_POS=";
        s+= sherlock_init_pos.str();
        s+= "\nSHERLOCK_INIT_HP=";
        s+= to_string(sherlock_init_hp);
        s+= "\nSHERLOCK_INIT_EXP=";
        s+= to_string(sherlock_init_exp);
        s+= "\nWATSON_MOVING_RULE=";
        s+= watson_moving_rule;
        s+= "\nWATSON_INIT_POS=";
        s+= watson_init_pos.str();
        s+="\nWATSON_INIT_HP=";
        s+= to_string(watson_init_hp);
        s+="\nWATSON_INIT_EXP=";
        s+= to_string(watson_init_exp);
        s+= "\nCRIMINAL_INIT_POS=";
        s+= criminal_init_pos.str();
        s+="\nNUM_STEPS=";
        s+= to_string(num_steps);
        s+="\n]";
        return s;
    }

    int get_map_num_rows(){
        return map_num_rows;
    }

    int get_map_num_cols(){
        return map_num_cols;
    }

    int get_max_num_moving_objects(){
        return max_num_moving_objects;
    }

    int get_num_walls(){
        return num_walls;
    }

    Position * get_arr_walls(){
        return arr_walls;
    }

    int get_num_fake_walls(){
        return num_fake_walls;
    }

    Position * get_arr_fake_walls(){
        return arr_fake_walls;
    }

    string get_sherlock_moving_rule(){
        return sherlock_moving_rule;
    }

    Position get_sherlock_init_pos(){
        return sherlock_init_pos;
    }

    int get_sherlock_init_hp(){
        return sherlock_init_hp;
    }

    int get_sherlock_init_exp(){
        return sherlock_init_exp;
    }

    string get_watson_moving_rule(){
        return watson_moving_rule;
    }

    Position get_watson_init_pos(){
        return watson_init_pos;
    }

    int get_watson_init_hp(){
        return watson_init_hp;
    }

    int get_watson_init_exp(){
        return watson_init_exp;
    }

    Position get_criminal_init_pos(){
        return criminal_init_pos;
    }

    int get_num_steps(){
        return num_steps;
    }
    friend class TestStudyInPink;
};


class BaseItem{


    public:

    virtual bool canUse ( Character * obj , Robot * robot ) = 0;
    virtual void use ( Character * obj , Robot * robot ) = 0;
    virtual void use(Character * obj, string nameRobot) = 0;



    virtual string str() = 0;
    friend class TestStudyInPink;
};

class MagicBook : public BaseItem {
    public:
    bool canUse ( Character * obj , Robot * robot ){
        if(obj->getExp() <= 350) return true;
        else return false;
    }


    void use ( Character * obj , Robot * robot ){
        if((obj->getExp()*25) % 100 != 0) obj->setExp(obj->getExp()*125/100 + 1);
        else obj->setExp(obj->getExp()*125/100);
    }
    void use(Character * obj, string nameRobot){}
   

    string str(){
        return "MagicBook";
    }
    friend class TestStudyInPink;
};

class EnergyDrink : public BaseItem{
    public:
    bool canUse ( Character * obj , Robot * robot ){
        if(obj->getHp() <= 100) return true;
        else return false;
    }


    void use ( Character * obj , Robot * robot ){
        if((obj->getHp() * 20) % 100 != 0) obj->setHp(obj->getHp() *120/100 + 1);
        else obj->setHp(obj->getHp() *120/100);
    }
    void use(Character * obj, string nameRobot){}
   

    string str(){
        return "EnergyDrink";
    }
    friend class TestStudyInPink;
};

class FirstAid : public BaseItem{
    public:
    bool canUse ( Character * obj , Robot * robot ){
        if((obj->getHp() <= 100) || (obj->getExp() <= 350)) return true;
        else return false;
    }


    void use ( Character * obj , Robot * robot ){
        if((obj->getHp()*50) % 100 != 0) obj->setHp(obj->getHp() *150/100 + 1);
        else obj->setHp(obj->getHp() *150/100);
    }

    void use(Character * obj, string nameRobot){}

    string str(){
        return "FirstAid";
    }
    friend class TestStudyInPink;
};

class ExcemptionCard : public BaseItem{
    public:
    bool canUse ( Character * obj , Robot * robot ){
        if((obj->getName() == "Sherlock") && (obj->getHp() % 2 == 1)) return true;
        else return false;
    }

    void use ( Character * obj , Robot * robot ){
        
    }
    void use(Character * obj, string nameRobot){}

    string str(){
        return "ExcemptionCard";
    }
    friend class TestStudyInPink;
};

class PassingCard : public  BaseItem{

    public:
    string challenge;
    PassingCard(){

    }

    PassingCard(string robot){
        challenge = robot;
    }
    bool canUse ( Character * obj , Robot * robot ){
        if(obj->getName() == "Watson" && (obj->getHp() % 2 == 0)) return true;
        else return false;
    }

    void use ( Character * obj , Robot * robot ){
        // if(challenge != "all"){
        //     if(challenge != robot->getName()){
        //         obj->setExp(obj->getExp() - 50);
        //     }
        // }
    }

    void use(Character * obj, string nameRobot){
        if(challenge != "all"){
            if(challenge != nameRobot){
                obj->setExp(obj->getExp() - 50);
            }
        }
    }

    string str(){
        return "PassingCard";
    }


    string get_challenge(){
        return this->challenge;
    }
    friend class TestStudyInPink;
};

class Robot : public MovingObject{
    public:
    RobotType robot_type;
    BaseItem * item = NULL;
    

    
    Robot(){}
    ~Robot(){
    }

    Robot(int index , const Position & init_pos , Map * map) : MovingObject(index, init_pos, map){
    }

    BaseItem * getItem(){
        return this->item;
    }


    Position getNextPosition(){
        return npos;
    }

    void move(){}
    string str() const{
        return "";
    }

    void get_Item(Position draft_pos){
        int p = draft_pos.getRow() * draft_pos.getCol();
        int a = 0;
        while(p > 9){
            while(p != 0){
            a += p%10;
            p/=10;
        }
        p = a;
        a = 0;
        }  
        if(p == 0 || p == 1){
            MagicBook * d_tem = new MagicBook;
            this->item = d_tem;
        }
        else if(p == 2 || p == 3){
            EnergyDrink * d_tem = new EnergyDrink;
            this->item = d_tem;
        }
        else if(p == 4 || p == 5){
            FirstAid * d_tem = new FirstAid;
            this->item = d_tem;
        }
        else if(p == 6 || p == 7){
            ExcemptionCard * d_tem = new ExcemptionCard;
            this->item = d_tem;
        }
        else if(p == 8 || p == 9){
            PassingCard * d_tem = new PassingCard;
            int t = (pos.getRow() * 11 + pos.getCol())%4;
            if(t == 0) d_tem->challenge = "RobotS";
            else if(t == 1) d_tem->challenge = "RobotC";
            else if(t == 2) d_tem->challenge = "RobotSW";
            else if(t == 3) d_tem->challenge = "all";
            this->item = d_tem;
        }
    }
    friend class TestStudyInPink;
    
};

class RobotC : public Robot{
    public:
    Criminal* criminal;

    
    RobotC(){
        this->name = "RobotC";
    }

    RobotC ( int index , const Position & init_pos , Map * map , Criminal * criminal ) : Robot(index, init_pos, map) {
        robot_type = C;
        this->criminal = criminal;
        this->name = "RobotC";
    }

    Position getNextPosition(){
        Sherlock *sherlock = new Sherlock;
        if(map->isValid(criminal->getCurrentPosition(), sherlock )){
            delete sherlock;
             return criminal->getPreCri();

        }
        else{
            delete sherlock;
            return npos;
        }
    }

    void move(){
        Position draft = this->getNextPosition();
        if(!(draft.isEqual(npos))){
            pos = draft;
        }
    }

    int getDistance(Sherlock * Sherlock){
        Position draft_pos = Sherlock->getCurrentPosition();
        return (abs(this->pos.getRow() - draft_pos.getRow()) + abs(this->pos.getCol() - draft_pos.getCol()));
    }

    int getDistance(Watson * watson){
        Position draft_pos = watson->getCurrentPosition();
        return (abs(this->pos.getRow() - draft_pos.getRow()) + abs(this->pos.getCol() - draft_pos.getCol()));
    }

    string str() const{
        string s;
        s+= "Robot[pos=";
        s+= this->pos.str();
        s+= ";type=C";
        s+= ";dist=";
        s+= "]";
        return s;
    }

    BaseItem * getItem(){
        return this->item;
    }
    friend class TestStudyInPink;
};

class RobotS : public Robot{
    public:
    Criminal* criminal;
    Sherlock* sherlock;

    
    RobotS(){
        this->name = "RobotS";
    }

    RobotS ( int index , const Position & init_pos , Map * map ,Criminal * criminal , Sherlock * sherlock ) : Robot(index, init_pos, map) {
        robot_type = S;
        this->criminal = criminal;
        this->sherlock = sherlock;
        this->name = "RobotS";
    }

    Position getNextPosition(){
        Position sherlock_pos = sherlock->getCurrentPosition();
        int distance;
        int i = -1;

        Position draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            distance = abs(this->pos.getRow() - 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol());
            i = 0;
        }

        draft_pos = this->pos;
        draft_pos.setCol(this->pos.getCol() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((distance > (abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol()))) || (i == -1)){
            distance = abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol());
            i = 1;
        }
        }

        draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((distance > (abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol()))) || (i == -1)){
            distance = abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol());
            i = 2;
        } 
        }
         
        draft_pos = this->pos;
        draft_pos.setCol(this->pos.getCol() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((distance > (abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol()))) || (i == -1)){
            distance = abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol());
            i = 3;
        }  
        }
        
        draft_pos = this->pos;
        if(i == 0) draft_pos.setRow(this->pos.getRow() - 1);
        else if(i == 1) draft_pos.setCol(this->pos.getCol() + 1);
        else if(i == 2) draft_pos.setRow(this->pos.getRow() + 1);
        else if(i == 3) draft_pos.setCol(this->pos.getCol() - 1);
        else if(i == -1) return npos;
        
        return draft_pos;
    }

    void move(){
        Position draft = this->getNextPosition();
        if(!(draft.isEqual(npos))){
            pos = draft;
        }
    }

    int getDistance(){
        Position draft_pos = sherlock->getCurrentPosition();
        return (abs(this->pos.getRow() - draft_pos.getRow()) + abs(this->pos.getCol() - draft_pos.getCol()));
    }


    string str() const{
        Position draft_pos = sherlock->getCurrentPosition();
        string s;
        s+= "Robot[pos=";
        s+= this->pos.str();
        s+= ";type=S";
        s+= ";dist=";
        s+= to_string(abs(this->pos.getRow() - draft_pos.getRow()) + abs(this->pos.getCol() - draft_pos.getCol()));
        s+= "]";
        return s;
    }

    BaseItem * getItem(){
        return this->item;
    }
    friend class TestStudyInPink;
};

class RobotW : public Robot{
    public:
    Criminal* criminal;
    Watson* watson;

    
    RobotW(){
        this->name = "RobotW";
    }

    RobotW ( int index , const Position & init_pos , Map * map , Criminal * criminal , Watson * watson ) : Robot(index, init_pos, map){
        robot_type = W;
        this->criminal = criminal;
        this->watson = watson;
        this->name = "RobotW";
    }

    Position getNextPosition(){
        Position watson_pos = watson->getCurrentPosition();
        if(watson_pos.isEqual(npos)) return npos;
        int distance;
        int i = -1;
        Sherlock *sherlock = new Sherlock;

        Position draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            distance = abs(this->pos.getRow() - 1 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol());
            i = 0;
        }
        
        draft_pos = this->pos;
        draft_pos.setCol(this->pos.getCol() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((distance > (abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() + 1 - watson_pos.getCol()))) || (i == -1)){
            distance = abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() + 1 - watson_pos.getCol());
            i = 1;
        } 
        }
        
        draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((distance > (abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol()))) || (i == -1)){
            distance = abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol());
            i = 2;
        } 
        }
        
        draft_pos = this->pos;
        draft_pos.setCol(this->pos.getCol() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((distance > (abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() - 1 - watson_pos.getCol()))) || (i == -1)){
            distance = abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() - 1 - watson_pos.getCol());
            i = 3;
        }   
        }
        
        delete sherlock;
        draft_pos = this->pos;
        if(i == 0) draft_pos.setRow(this->pos.getRow() - 1);
        else if(i == 1) draft_pos.setCol(this->pos.getCol() + 1);
        else if(i == 2) draft_pos.setRow(this->pos.getRow() + 1);
        else if(i == 3) draft_pos.setCol(this->pos.getCol() - 1);
        else if(i == -1) return npos;
      
        return draft_pos;
     
       
    }

    void move(){
        Position draft = this->getNextPosition();
        if(!(draft.isEqual(npos))){
            pos = draft;
        }
    }

    int getDistance(){
        Position draft_pos = watson->getCurrentPosition();
        return (abs(this->pos.getRow() - draft_pos.getRow()) + abs(this->pos.getCol() - draft_pos.getCol()));
    }

    string str() const{
        Position draft_pos = watson->getCurrentPosition();
        string s;
        s+= "Robot[pos=";
        s+= this->pos.str();
        s+= ";type=W";
        s+= ";dist=";
        s+= to_string(abs(this->pos.getRow() - draft_pos.getRow()) + abs(this->pos.getCol() - draft_pos.getCol()));
        s+= "]";
        return s;
    }
    BaseItem * getItem(){
        return this->item;
    }

    friend class TestStudyInPink;
};

class RobotSW : public Robot{
    public:
    Criminal* criminal;
    Sherlock* sherlock;
    Watson* watson;

    
    RobotSW(){
        this->name = "RobotSW";
    }

    RobotSW ( int index , const Position & init_pos , Map * map ,Criminal * criminal , Sherlock * sherlock , Watson* watson ) :Robot(index, init_pos, map){
        robot_type = SW;
        this->criminal = criminal;
        this->sherlock = sherlock;
        this->watson = watson;
        this->name = "RobotSW";
    }

    Position getNextPosition(){
        Position sherlock_pos = sherlock->getCurrentPosition();
        Position watson_pos = watson->getCurrentPosition();
        int sum_distance;
        int i = -1;

        Position draft_pos = this->pos;
        draft_pos.setRow(this->pos.getRow() - 2);
        if((map->isValid(draft_pos, sherlock ))){
            sum_distance = abs(this->pos.getRow() - 2 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol()) + abs(this->pos.getRow() - 2 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol());
            i = 0;
        }
        
        draft_pos = this->pos;
        draft_pos.setRow(pos.getRow() - 1);
        draft_pos.setCol(pos.getCol() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow() - 1 - watson_pos.getRow()) + abs(this->pos.getCol() + 1 - watson_pos.getCol()) + abs(this->pos.getRow() - 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() - 1 - watson_pos.getRow()) + abs(this->pos.getCol() + 1 - watson_pos.getCol()) + abs(this->pos.getRow() - 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol());
            i = 1;
        }
        }
        
        draft_pos = this->pos;
        draft_pos.setCol(pos.getCol() + 2);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() + 2 - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() + 2 - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() + 2 - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() + 2 - sherlock_pos.getCol());
            i = 2;
        }
        }
        
        draft_pos = this->pos;
        draft_pos.setRow(pos.getRow() + 1);
        draft_pos.setCol(pos.getCol() + 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() + 1 - watson_pos.getCol()) + abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() + 1 - watson_pos.getCol()) + abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() + 1 - sherlock_pos.getCol());
            i = 3;
        }
        }
        
        draft_pos = this->pos;
        draft_pos.setRow(pos.getRow() + 2);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow()  + 2 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol()) + abs(this->pos.getRow() + 2 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() + 2 - watson_pos.getRow()) + abs(this->pos.getCol() - watson_pos.getCol()) + abs(this->pos.getRow() + 2 - sherlock_pos.getRow()) + abs(this->pos.getCol() - sherlock_pos.getCol());
            i = 4;
        }
        }
        
        draft_pos = this->pos;
        draft_pos.setRow(pos.getRow() + 1);
        draft_pos.setCol(pos.getCol() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() - 1 - watson_pos.getCol()) + abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() + 1 - watson_pos.getRow()) + abs(this->pos.getCol() - 1 - watson_pos.getCol()) + abs(this->pos.getRow() + 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol());
            i = 5;
        }
        }
        
        draft_pos = this->pos;
        draft_pos.setCol(pos.getCol() - 2);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() - 2 - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() - 2 - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() - watson_pos.getRow()) + abs(this->pos.getCol() - 2 - watson_pos.getCol()) + abs(this->pos.getRow() - sherlock_pos.getRow()) + abs(this->pos.getCol() - 2 - sherlock_pos.getCol());
            i = 6;
        }
        }

        draft_pos = this->pos;
        draft_pos.setRow(pos.getRow() - 1);
        draft_pos.setCol(pos.getCol() - 1);
        if((map->isValid(draft_pos, sherlock ))){
            if((sum_distance > abs(this->pos.getRow() - 1 - watson_pos.getRow()) + abs(this->pos.getCol() - 1 - watson_pos.getCol()) + abs(this->pos.getRow() - 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol())) || (i == -1)){
            sum_distance = abs(this->pos.getRow() - 1 - watson_pos.getRow()) + abs(this->pos.getCol() - 1 - watson_pos.getCol()) + abs(this->pos.getRow() - 1 - sherlock_pos.getRow()) + abs(this->pos.getCol() - 1 - sherlock_pos.getCol());
            i = 7;
        }
        }
        

        draft_pos = this->pos;

        if(i == 0){
            draft_pos.setRow(pos.getRow() - 2);
        }
        else if(i == 1){
            draft_pos.setRow(pos.getRow() - 1);
            draft_pos.setCol(pos.getCol() + 1);
        }
        else if(i == 2){
            draft_pos.setCol(pos.getCol() + 2);
        }
        else if(i == 3){
            draft_pos.setRow(pos.getRow() + 1);
            draft_pos.setCol(pos.getCol() + 1);
        }
        else if(i == 4){
           draft_pos.setRow(pos.getRow() + 2);
        }
        else if(i == 5){
            draft_pos.setRow(pos.getRow() + 1);
            draft_pos.setCol(pos.getCol() - 1);
        }
        else if(i == 6){
            draft_pos.setCol(pos.getCol() - 2);
        }
        else if(i == 7){
            draft_pos.setRow(pos.getRow() - 1);
            draft_pos.setCol(pos.getCol() - 1);
        }
        else if(i == -1) return npos;

        return draft_pos;

    }

    void move(){
        Position draft = this->getNextPosition();
        if(!(draft.isEqual(npos))){
            pos = draft;
        }
    }

    int getDistance(){
        Position draft_pos2 = sherlock->getCurrentPosition();
        Position draft_pos1 = watson->getCurrentPosition();
        return (abs(this->pos.getRow() - draft_pos1.getRow()) + abs(this->pos.getCol() - draft_pos1.getCol()) + abs(this->pos.getRow() - draft_pos2.getRow()) + abs(this->pos.getCol() - draft_pos2.getCol()) );
    }

    string str() const{
        Position draft_pos2 = sherlock->getCurrentPosition();
        Position draft_pos1 = watson->getCurrentPosition();
        string s;
        s+= "Robot[pos=";
        s+= this->pos.str();
        s+= ";type=SW";
        s+= ";dist=";
        s+= to_string(abs(this->pos.getRow() - draft_pos1.getRow()) + abs(this->pos.getCol() - draft_pos1.getCol()) + abs(this->pos.getRow() - draft_pos2.getRow()) + abs(this->pos.getCol() - draft_pos2.getCol()));
        s+= "]";
        return s;
    }

    BaseItem * getItem(){
        return this->item;
    }
    friend class TestStudyInPink;
};


struct Node{
    BaseItem * data;
    Node* next;
};

struct LList
{
    Node* head;
};


class BaseBag{
    protected:
    LList bag;
    int max_item;
    int real_item = 0;
    Robot* robot;
    Character * obj;

    public:
    BaseBag(){
        bag.head = NULL;
    }

    virtual bool insert ( BaseItem * item ){
        if(real_item == max_item) return false;
        else{
        if(bag.head != NULL){    
        Node* pnew = new Node;
        pnew->data = item;
        pnew->next = bag.head;
        bag.head = pnew;
        }
        else{
            bag.head = new Node;
            bag.head->data=item;
            bag.head->next=NULL;
        }
        real_item++;
        return true;
        }
    }

    virtual BaseItem * get (){
        Node * draft_bag = this->bag.head;
        Node * pre = this->bag.head;
        for(int i = 0; i < this->real_item; i++){
            if((draft_bag->data->canUse(obj, this->robot))){
                if(i == 1){
                    bag.head->next = draft_bag->next;
                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                else if(i == 0){
                    bag.head = bag.head->next;
                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                else {
                    Node * draft = bag.head;
                    bag.head = bag.head->next;
                    draft->next = draft_bag->next;
                    pre->next = draft;


                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
            }
            draft_bag = draft_bag->next;
            pre = pre->next;
            if(i == 0) pre = this->bag.head;
        }
        return NULL;
    }

    virtual BaseItem * get_khoa (){
        Node * draft_bag = this->bag.head;
        Node * pre = this->bag.head;
        for(int i = 0; i < this->real_item; i++){
            if((draft_bag->data->canUse(obj, this->robot)) && (draft_bag->data->str() != "ExcemptionCard") && (draft_bag->data->str() != "PassingCard")){
                if(i == 1){
                    bag.head->next = draft_bag->next;
                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                else if(i == 0){
                    bag.head = bag.head->next;
                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                else {
                    Node * draft = bag.head;
                    bag.head = bag.head->next;
                    draft->next = draft_bag->next;
                    pre->next = draft;


                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
            }
            draft_bag = draft_bag->next;
            pre = pre->next;
            if(i == 0) pre = this->bag.head;
        }
        return NULL;
    }

    virtual BaseItem * get ( ItemType itemType ) {
        string name_item;
        if (itemType == MAGIC_BOOK){
            MagicBook magicbook;
            name_item = "MagicBook";
        }
        else if(itemType == ENERGY_DRINK){
            EnergyDrink energydrink;
            name_item = "EnergyDrink";
        }
        else if(itemType == FIRST_AID){
            FirstAid item;
            name_item = "FirstAid";
        }
        else if(itemType == EXCEMPTION_CARD){
            ExcemptionCard item;
            name_item = "ExcemptionCard";
        }
        else if(itemType == PASSING_CARD){
            PassingCard item;
            name_item = "PassingCard";
        }

            Node * pre = this->bag.head;
            Node * draft_bag = this->bag.head;
            for(int i = 0; i < this->real_item; i++){  
                if(draft_bag->data->str() == name_item){
                    if(i == 1){
                    bag.head->next = draft_bag->next;
                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                else if(i == 0){
                    bag.head = bag.head->next;
                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                else {
                    Node * draft = bag.head;
                    bag.head = bag.head->next;
                    draft->next = draft_bag->next;
                    pre->next = draft;


                    draft_bag->next = NULL;
                    real_item--;
                    return draft_bag->data;
                }
                }

            draft_bag = draft_bag->next;
            pre = pre->next;
            if(i == 0) pre = this->bag.head;
            }
            return NULL;
    }

    virtual string str () const {
        string s;
        Node * draft_bag = bag.head;

        s += "Bag[count=";
        s += to_string(real_item);
        s += ";";
        for(int i = 0; i < real_item; i++){
            s += draft_bag->data->str();
            s += ",";
            draft_bag = draft_bag->next;
        }
        if(real_item != 0) s.erase(s.length()- 1);
        s += "]";
        return s;
    }

    int getRealitem(){
        return real_item;
    }

    int getCount(){
        return real_item;
    }
    friend class TestStudyInPink;
};

class SherlockBag : public BaseBag{
    public:
    Sherlock * sherlock;

    SherlockBag(){}
    
    SherlockBag(Sherlock * sherlock){
        bag.head = NULL;
        this->sherlock = sherlock;
        this->max_item = 13;
        this->obj = sherlock;
    }
    

    friend class TestStudyInPink;
};

class WatsonBag : public BaseBag{
    public:
    Watson * watson;

    WatsonBag(){}
    WatsonBag(Watson * watson){
        bag.head = NULL;
        this->watson = watson;
        this->max_item = 15;
        this->obj = watson;
    }

    
    friend class TestStudyInPink;
};


class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(){}
    StudyPinkProgram(const string & config_file_path){
        
        config = new Configuration(config_file_path);                                                                                                                                  
        map= new Map(config->get_map_num_rows(), config->get_map_num_cols() , config->get_num_walls() , config->get_arr_walls() ,config->get_num_fake_walls() , config->get_arr_fake_walls() ) ;    
        sherlock = new Sherlock( 1, config->get_sherlock_moving_rule() , config->get_sherlock_init_pos() , map , config->get_sherlock_init_hp() , config->get_sherlock_init_exp() );
          
        watson= new Watson( 2, config->get_watson_moving_rule() , config->get_watson_init_pos() , map , config->get_watson_init_hp() , config->get_watson_init_exp() );
        criminal = new Criminal( 0 , config->get_criminal_init_pos() ,  map , sherlock , watson ) ;

        arr_mv_objs = new ArrayMovingObject(config->get_num_steps()/3 + 3);
        arr_mv_objs->add(criminal);
        arr_mv_objs->add(sherlock);
        arr_mv_objs->add(watson);
    }


    bool isStop() const{
        if((sherlock->getHp() == 1) && (watson->getHp() == 1)){
            return true;
        }
        else if(arr_mv_objs->get(0)->getCurrentPosition().isEqual(arr_mv_objs->get(1)->getCurrentPosition()) || arr_mv_objs->get(0)->getCurrentPosition().isEqual(arr_mv_objs->get(2)->getCurrentPosition())) return true;
        else return false;
    }

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO

        SherlockBag bag_sherlock(sherlock);
        WatsonBag bag_watson(watson);

        

        int count_index = 2;
        //Position draft_pos = arr_mv_objs->get(0)->getCurrentPosition();
        for (int istep = 0; istep < config->get_num_steps(); ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();

                //Trao doi the:
                if(i == 1 || i ==2){
                if(arr_mv_objs->get(1)->getCurrentPosition().isEqual(arr_mv_objs->get(2)->getCurrentPosition())){
                    while(bag_sherlock.get(PASSING_CARD) != NULL){
                        PassingCard * item_watson = new PassingCard;
                        bag_watson.insert(item_watson);
                    }

                    while(bag_watson.get(EXCEMPTION_CARD) != NULL){
                        ExcemptionCard * item_sherlock = new ExcemptionCard;
                        bag_sherlock.insert(item_sherlock);
                    }
                }
            }

                //Sherlock gap robot:
                bool check_win = false;
                    for(int j = 3;  j < arr_mv_objs->size(); j++){
                        if(arr_mv_objs->get(1)->getCurrentPosition().isEqual(arr_mv_objs->get(j)->getCurrentPosition())){  
                            bool check_item = true;
                            if(bag_sherlock.get(EXCEMPTION_CARD) != NULL){
                                    check_item = false;
                                }

                            BaseItem * draft_item = arr_mv_objs->get(j)->getItem();
                            if(arr_mv_objs->get(j)->getName() == "RobotS" ){
                                if(arr_mv_objs->get(1)->getExp() > 400){
                                    bag_sherlock.insert(draft_item);
                                }
                                else{
                                    if(check_item){
                                        arr_mv_objs->get(1)->setExp(arr_mv_objs->get(1)->getExp() - arr_mv_objs->get(1)->getExp()*10/100);
                                    }
                                }
                                                            
                            }
                            else if(arr_mv_objs->get(j)->getName() == "RobotW"){
                                bag_sherlock.insert(arr_mv_objs->get(j)->getItem());
                            }
                            else if(arr_mv_objs->get(j)->getName() == "RobotSW"){
                                if(arr_mv_objs->get(1)->getExp() > 300 && arr_mv_objs->get(1)->getHp() > 335){
                                    bag_sherlock.insert(arr_mv_objs->get(j)->getItem());
                                }
                                else{
                                    if(check_item){
                                        arr_mv_objs->get(1)->setExp(arr_mv_objs->get(1)->getExp() - arr_mv_objs->get(1)->getExp()*15/100);
                                        arr_mv_objs->get(1)->setHp(arr_mv_objs->get(1)->getHp() - arr_mv_objs->get(1)->getHp()*15/100);
                                    } 
                                }
                            }
                            else if(arr_mv_objs->get(j)->getName() == "RobotC"){
                                if(arr_mv_objs->get(1)->getExp() > 500){
                                    arr_mv_objs->get(1)->setPos(arr_mv_objs->get(0)->getCurrentPosition());
                                    check_item = true;
                                    break;
                                }
                                else{
                                    bag_sherlock.insert(arr_mv_objs->get(j)->getItem());
                                }
                            }

                            BaseItem *draft_bag = bag_sherlock.get_khoa();
                            if(draft_bag != NULL)
                            draft_bag->use(sherlock, NULL);
                            }
                        }
                    if(check_win){
                        printStep(istep);
                        break;
                    }

                    //Watson danh robot:
                        for(int j = 3;  j < arr_mv_objs->size(); j++){
                        if(arr_mv_objs->get(2)->getCurrentPosition().isEqual(arr_mv_objs->get(j)->getCurrentPosition())){
                            bool check_item = false;
                            BaseItem * draft_item = bag_watson.get(PASSING_CARD);
                            if(draft_item != NULL){
                                    check_item = true;
                                }
                            if(arr_mv_objs->get(j)->getName() == "RobotS" ){
                            }

                            else if(arr_mv_objs->get(j)->getName() == "RobotW"){
                                if(check_item){
                                    
                                    draft_item->use(watson, "RobotW");
                                }
                                else{
                                    if(arr_mv_objs->get(2)->getHp() > 350){
                                        bag_watson.insert(arr_mv_objs->get(j)->getItem());
                                    }
                                    else{
                                        arr_mv_objs->get(2)->setHp(arr_mv_objs->get(2)->getHp() - arr_mv_objs->get(2)->getHp()*5/100);
                                    }
                                }
                            }
                            else if(arr_mv_objs->get(j)->getName() == "RobotSW"){
                                if(check_item){
                                    draft_item->use(watson, "RobotSW");
                                }
                                else{
                                    if(arr_mv_objs->get(2)->getExp() > 600 && arr_mv_objs->get(2)->getHp() > 165){
                                        bag_watson.insert(arr_mv_objs->get(j)->getItem());
                                    }
                                    else{
                                        arr_mv_objs->get(2)->setExp(arr_mv_objs->get(2)->getExp() - arr_mv_objs->get(2)->getExp()*15/100);
                                        arr_mv_objs->get(2)->setHp(arr_mv_objs->get(2)->getHp() - arr_mv_objs->get(2)->getHp()*15/100);
                                    }
                                }
                            }
                            else if(arr_mv_objs->get(j)->getName() == "RobotC"){
                                bag_watson.insert(arr_mv_objs->get(j)->getItem());
                            }

                            BaseItem * draft_bag = bag_watson.get_khoa();
                            if( draft_bag != NULL){
                                draft_bag->use(watson, NULL);
                            }
                            }
                        }
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
            if (isStop()){
                    break;
                }
            
            //Tao robot:
                if(istep == 2){
                    count_index++;
                    RobotC * robotC = new RobotC(count_index , criminal->getPreCri() , map , criminal);
                    robotC->get_Item(robotC->getCurrentPosition());
                    arr_mv_objs->add(robotC);
                    arr_mv_objs->get(count_index)->move();
                    if (verbose) {
                    printStep(istep);
                }
                    // draft_pos = arr_mv_objs->get(0)->getCurrentPosition();
                }
                else if(istep % 3 == 2){
                    int sherlock_distance = criminal->getPreCri().get_distance(arr_mv_objs->get(1)->getCurrentPosition());
                    int watson_distance = criminal->getPreCri().get_distance(arr_mv_objs->get(2)->getCurrentPosition());
                    count_index++;

                    if(sherlock_distance < watson_distance){
                        RobotS * robotS = new RobotS(count_index, criminal->getPreCri(), map, criminal, sherlock);
                        robotS->get_Item(robotS->getCurrentPosition());
                        arr_mv_objs->add(robotS);
                    }
                    else if(sherlock_distance > watson_distance){
                        RobotW * robotW = new RobotW(count_index, criminal->getPreCri(), map, criminal, watson);
                        robotW->get_Item(robotW->getCurrentPosition());
                        arr_mv_objs->add(robotW);
                    }
                    else{
                        RobotSW * robotSW = new RobotSW(count_index, criminal->getPreCri(), map, criminal, sherlock, watson);
                        robotSW->get_Item(robotSW->getCurrentPosition());
                        arr_mv_objs->add(robotSW);
                    }
                    arr_mv_objs->get(count_index)->move();
                    if (verbose) {
                    printStep(istep);
                }
                    // draft_pos = arr_mv_objs->get(0)->getCurrentPosition();
                }          
        }

        printResult();
    }

    ~StudyPinkProgram(){
        delete config;
        delete map;
        delete sherlock;
        delete criminal;
        delete watson;
        delete arr_mv_objs;
    }
    friend class TestStudyInPink;
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
