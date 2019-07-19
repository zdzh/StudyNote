#  go 学习笔记

## 包

Go使用`package`将源文件打包成包，main函数所在的文件必须打包成main，编译器才会将其编译为可执行文件，否则将其编译为包。

导入包时，使用`import`语句，GO语言要求导入的包必须是被使用的包，若导入包未被使用，编译器会直接报错，无法通过。

导入包时，程序会首先运行包里面的`init`函数，当我们只需要执行`init`函数，而暂时不引用包的变量或函数时，可以使用匿名导入的方式，防止编译器报错，匿名导入只需要在包名的前面加入`_`即可，如下所示：

```go
import _ "fmt"
```

包的成员的外部可见性与成员的名称的大小写有关，当成员名称首字母为大写时，则该成员时导出的，引用该包的其他包可以访问这个成员；否则该成员未导出。

## 语句

Go语言不需要在语句或者声明的末尾添加分号，除非一行上有多条语句。实际上，编译器会主动把特定符号后的换行符转换为分号, 因此换行符添加的位置会影响Go代码的正确解析

1. 函数的左括号必须位于函数名之后，且在行尾，不能独占一行，（其他相似情况下类似）
2. 表达式x+y中，可以在+之后换行，不能在+之前换行

c类语言中i++为表达式，而go中，i++是语句而非表达式，且++i非法

 ```go
*p++   //增加p指针指向的变量的值，而不改变p自身，与c/c++不同
 ```

### if语句

go的条件语句结构如下所示

```go
if 语句;布尔表达式{
 	语句   
}
```

与其他类c语言不同的是，go中的if语句不需要`()`但必须带有`{}`.同时在布尔表达式之前可以插入语句用于声明局部变量或给变量赋值等。

### 循环语句

go中的循环语句相关的关键字只有`for`，与if语句相同，for语句不需要`()`但必须包含`{}`,for语句一般结构如下所示

```go
for 语句1;布尔表达式;语句2{
	...    
}
```

与c语言的for循环类似，同样包括三部分语句，且部分语句可以省略

```go
	for i := 0; i < 10; i++ {
		fmt.Println(i)
	}
	for i := 0; i < 10; {
		fmt.Println(i)
		i++
	}
	var j int
	for ; j < 10; j++ {
		fmt.Println(j)
	}
	j = 0
	for {
		if j == 10 {
			fmt.Println("break frome  for1")
			break
		}
		j++
	}
	j = 0
	for j < 10 {
		fmt.Print(j)
		j++
	}
```

当for后面不接任何子语句时，该for语句为死循环。当for后面只含有布尔表达式时，可以将前后的分隔符省略。

for语句经常搭配`range`使用，`range`用于slice或map等类似于其他语言中的迭代器的时成分

```go
s :="hello word"
var a []int = []int{1,2,3,4}
for i,j := range(s){
    ...
}
for k,v:= range(a){
    ...
}
```

## 复合类型

不同类型间不能进行直接赋值操作

### 数组

数组长度是数组类型的一部分，`[3]int`和`[4]int`属于不同类型

```go
p := [3]int{1,2,3}
p = [4]int{1,2,3,4}    //error
```

与其他语言不同，go**函数的数组形参包采用副本的形式传入**，如果要对数组本身进行修改，需要使用指针形参，或者使用`slice`

```go
func test(a [4]int)[4]int{
	for i,j := range a{
		a[i] = j+1
	}
	return a
}

func main() {
	var a = [4]int{1,2,3,4}
	fmt.Println(a)       //1，2，3，4
	var b = test(a)
	fmt.Println(a)      //1,2,3,4
	fmt.Println(b)      //2,3,4,5
	
}
```

### slice

slice行为与数组类似，其底层包含一个数组，相较于数组，slice更加灵活，其长度可以动态改变，且作为函数参数时，其传递方式类似于引用，即被调函数内部的修改可以影响到主函数中的slice。

 切片声明时不需要指定大小，系统自动生成

```go
s := []int{1,2,3,4}       //与数组不同，不需要指定大小
```

值为`nil`的slice没有底层数组，与nil相等的slice长度为0，当长度为0的slice不一定是nil

```go
var s []int // len(s) == 0, s == nil
s = nil // len(s) == 0, s == nil
s = []int(nil) // len(s) == 0, s == nil
s = []int{} // len(s) == 0, s != nil
```

内置的make函数创建一个指定元素类型、长度和容量的slice。容量部分可以省略，在这种情况下，容量将等于长度。

```go
make([]T, len)
make([]T, len, cap) // same as make([]T, cap)[:len]
```

内置的append函数用于向slice追加元素：

```go
var runes []rune
for _, r := range "Hello, 世界" {
runes = append(runes, r)
}
fmt.Printf("%q\n", runes) // "['H' 'e' 'l' 'l' 'o' ',' ' ' '世' '界']"
```

### 结构体

结构体一般格式

```go
type name struct{
    ...
}
```

一个结构体可能同时含有导出成员和未导出成员

点操作符也可以和指向结构体的指针一起工作：

```go
var employeeOfTheMonth *Employee = &dilbert
employeeOfTheMonth.Position += " (proactive team player)"
```

相当于下面语句

```go
(*employeeOfTheMonth).Position += " (proactive team player)"
```

#### 结构体比较

若结构的所有成员都是可比较的，则结构体是可比较的当结构体所有成员都相等时，结构体变量相等

#### 嵌入和匿名

- 结构体可以嵌入到另一个结构体中

- 匿名成员的数据类型必须是命名的类型或指向一个命名的类型的指针

- 对于匿名嵌入，可以直接访问叶子属性而不需要给出完整的路径

  ```go
  type Point struct {
  X, Y int
  }  type Circle struct {
  Point
  Radius int
  }
  type Wheel struct {
  Circle
  Spokes int
  }  
  var w Wheel
  w.X = 8 // equivalent to w.Circle.Point.X = 8
  w.Y = 8 // equivalent to w.Circle.Point.Y = 8
  w.Radius = 5 // equivalent to w.Circle.Radius = 5
  w.Spokes = 20
  ```


## 函数

### 声明

函数声明包括函数名、形式参数列表、返回值列表（可省略）以及函数体。

```go
func name(parameter-list)(result-list){			    	
    body 
}
```

以下4中声明所代表的含义相同

```go
func add(x int, y int) int {return x + y}
func sub(x, y int) (z int) { z = x - y; return}
func first(x int, _ int) int { return x }
func zero(int, int) int { return 0 }
fmt.Printf("%T\n", add) // "func(int, int) int"
fmt.Printf("%T\n", sub) // "func(int, int) int"
fmt.Printf("%T\n", first) // "func(int, int) int"
fmt.Printf("%T\n", zero) // "func(int, int) int"
```

### 返回值

go支持多个返回值

如果一个函数将所有的返回值都显示的变量名，那么该函数的return语句可以省略操作数。这
称之为bare return。

```go
// CountWordsAndImages does an HTTP GET request for the HTML
// document url and returns the number of words and images in it.
func CountWordsAndImages(url string) (words, images int, err error) {
resp, err := http.Get(url)
if err != nil {
return
}
doc, err := html.Parse(resp.Body)
resp.Body.Close()
if err != nil {
err = fmt.Errorf("parsing HTML: %s", err)
return
}
words, images = countWordsAndImages(doc)
return
}
func countWordsAndImages(n *html.Node) (words, images int) { /* ... */ }
```

### 函数值

在GO中，函数被看作第一类值：函数拥有类型，可以赋值给其他变量，传递给函数，从函数返回，但是函数值之间是不可比较的，也不能用函数值作为map的key。

### 匿名函数

拥有函数名的函数只能在包级语法块中被声明，通过函数字面量（function	literal），我们可绕过这一限制，在任何表达式中表示一个函数值。函数字面量的语法和函数声明相似，区别 在于func关键字后没有函数名。函数值字面量是一种表达式，它的值被称为匿名函数（anonymous	function）。通过这种方式定义的函数可以访问完整的词法环境（lexical	environment）， 这意味着在函数中定义的内部函数可以引用该函数的变量，如下例所示：

```go
// squares返回一个匿名函数。
// 该匿名函数每次被调用时都会返回下一个数的平方。
func squares() func() int {
    var x int
    return func() int {
        x++
        return x * x
    }
}
func main() {
f := squares()
fmt.Println(f()) // "1"
fmt.Println(f()) // "4"
fmt.Println(f()) // "9"
fmt.Println(f()) // "16"
}
```

函数squares返回另一个类型为 func() int 的函数。对squares的一次调用会生成一个局部变量x并返回一个匿名函数。每次调用时匿名函数时，该函数都会先使x的值加1，再返回x的平方。第二次调用squares时，会生成第二个x变量，并返回一个新的匿名函数。新匿名函数操作的是第二个x变量。

###注意捕获迭代变量

```go
var rmdirs []func()
for _, d := range tempDirs() {
    dir := d // NOTE: necessary!
    os.MkdirAll(dir, 0755) // creates parent directories too
    rmdirs = append(rmdirs, func() {
    os.RemoveAll(dir)
	})
}
// ...do some work…
for _, rmdir := range rmdirs {
	rmdir() // clean up
}
```

在上面的程序中，for循环语句引入了新的词法块，循环 变量dir在这个词法块中被声明。在该循环中生成的所有函数值都共享相同的循环变量。需要注意，函数值中记录的是循环变量的内存地址，而不是循环变量某一时刻的值。以dir为例， 后续的迭代会不断更新dir的值，当删除操作执行时，for循环已完成，dir中存储的值等于最后一次迭代的值。这意味着，每次对os.RemoveAll的调用删除的都是相同的目录。这不是go或defer本身导致的，而是因为**它们都会等待循环结束后，再执行函数值。**
通常，为了解决这个问题，我们会引入一个与循环变量同名的局部变量，作为循环变量的副 本。比如下面的变量dir，虽然这看起来很奇怪，但却很有用。

```go
for
_, dir := range tempDirs() {
dir := dir // declares inner dir, initialized to outer dir
// ...
}
```

### 可变参数

参数数量可变的函数称为为可变参数函数。典型的例子就是fmt.Printf和类似函数。Printf首先接收一个的必备参数，之后接收任意个数的后续参数。在声明可变参数函数时，需要在参数列表的最后一个参数类型之前加上省略符号“...”，这表示
该函数会接收任意数量的该类型参数。

```go
func sum(vals...int) int {
    total := 0
    for _, val := range vals {
        total += val
    }
    return total
}
```

sum函数返回任意个int型参数的和。在函数体中,vals被看作是类型为[] int的切片。sum可以接收任意数量的int型参数：

```go
fmt.Println(sum()) // "0"
fmt.Println(sum(3)) // "3"
fmt.Println(sum(1, 2, 3, 4)) // "10"
```

在上面的代码中，调用者隐式的创建一个数组，并将原始参数复制到数组中，再把数组的一个切片作为参数传给被调函数。如果原始参数已经是切片类型，我们该如何传递给sum？只需在最后一个参数后加上省略符。下面的代码功能与上个例子中最后一条语句相同。

```go
values := []int{1, 2, 3, 4}
fmt.Println(sum(values...)) // "10"
```

虽然在可变参数函数内部，...int 型参数的行为看起来很像切片类型，但实际上，可变参数函数和以切片作为参数的函数是不同的。

```go
func f(...int) {}
func g([]int) {}
fmt.Printf("%T\n", f) // "func(...int)"
fmt.Printf("%T\n", g) // "func([]int)"
```

### Deferred函数

当defer语句被执行时，跟在defer后面的函数会被延迟执行。直到包含该defer语句的函数执行完毕时，defer后的函数才会被执行，不论包含defer语句的函数是通过return正常结束，还是由于panic导致的异常结束。你可以在一个函数中执行多条defer语句，它们的执行顺序与声明顺序相反。

defer语句经常被用于处理成对的操作，如打开、关闭、连接、断开连接、加锁、释放锁。通过defer机制，不论函数逻辑多复杂，都能保证在任何执行路径下，资源被释放。释放资源的defer应该直接跟在请求资源的语句后。

### Panic

Go的类型系统会在编译时捕获很多错误，但有些错误只能在运行时检查，如数组访问越界、空指针引用等。这些运行时错误会引起painc异常。
一般而言，当panic异常发生时，程序会中断运行，并立即执行在该goroutine中被延迟的函数（defer 机制）。随后，程序崩溃并输出日志信息。日志信息包括panic value和函数调用的堆栈跟踪信息。panic value通常是某种错误信息。对于每个goroutine，日志信息中都会有与之相对的，发生panic时的函数调用堆栈跟踪信息。通常，我们不需要再次运行程序去定位问题，日志信息已经提供了足够的诊断依据。因此，在我们填写问题报告时，一般会将panic异常和日志信息一并记录。

虽然Go的panic机制类似于其他语言的异常，但panic的适用场景有一些不同。由于panic会引起程序的崩溃，因此panic一般用于严重错误，如程序内部的逻辑不一致。

### Recover捕获异常

如果在deferred函数中调用了内置函数recover，并且定义该defer语句的函数发生了panic异常，recover会使程序从panic中恢复，并返回panic value。导致panic异常的函数不会继续运行，但能正常返回。在未发生panic时调用recoverrecover会返回nil。

```go
func Parse(input string) (s *Syntax, err error) {
defer func() {
if p := recover(); p != nil {
err = fmt.Errorf("internal error: %v"
, p)
}
}()
// ...parser...
}
```

deferred函数帮助Parse从panic中恢复。在deferred函数内部，panic value被附加到错误信息中；并用err变量接收错误信息，返回给调用者。我们也可以通过调用runtime.Stack往错误信息中添加完整的堆栈调用信息。

## 方法

  GO不支持类，但支持方法，可以为结构体或其他类型定义方法，方法就是一类带特殊的 **接收者** 参数的函数。方法接收者在它自己的参数列表内，位于 `func` 关键字和方法名之间。

  ```go
type Vertex struct {
  	X, Y float64
}
  
  func (v Vertex) Abs() float64 {        //定义结构体方法
  	return math.Sqrt(v.X*v.X + v.Y*v.Y)
  }
  
  func main() {
  	v := Vertex{3, 4}
      fmt.Println(v.Abs())                  //v.Abs() 调用方法
  }
  ```

  其形式类似于将函数声明中的形参放到函数名之前。  只能为同一个包的类型接收者声明方法，不能为其他包内定义的类型声明方法。 不能为内置类型（如：`int`）定义方法

  ```go
  type MyFloat float64
  
  func (f MyFloat) Abs() float64 {              //ture
  	if f < 0 {
  		return float64(-f)
  	}
  	return float64(f)
  }
  //cannot define new methods on non-local type float64
  //func (f float64) Abs() float64 {       
  //	if f < 0 {
  //		return float64(-f)
  //	}
  //	return float64(f)
  //} 
  func main() {
  	f := MyFloat(-math.Sqrt2)
  	fmt.Println(f.Abs())
  }
  ```

  ### 指针接收者	

使用指针接收者可以改变接收者自身的值

```go
type Vertex struct {
	X, Y float64
}

func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func (v *Vertex) Scale(f float64) {               //指针接收者
	v.X = v.X * f
	v.Y = v.Y * f
}

func main() {
	v := Vertex{3, 4}
    v.Scale(10)                 //v = {30,40}
	fmt.Println(v.Abs())
}
```

调用函数时，指针类型的形参必须接受一个指针；调用方法时接收者为变量时可以是指针也可以为值，编译器会自动解引用或取地址。

```go
var v Vertex
ScaleFunc(v, 5)  // 编译错误！
ScaleFunc(&v, 5) // OK

var v Vertex
v.Scale(5)  // OK
p := &v
p.Scale(10) // OK
```

*在现实的程序里，一般会约定如果Point这个类有一个指针作为接收器的方法，那么所有Point 的方法都必须有一个指针接收器，即使是那些并不需要这个指针接收器的函数。*

只有类型(Point)和指向他们的指针(*Point)，才是可能会出现在接收器声明里的两种接收器。 此外，为了避免歧义，在声明方法时，**如果一个类型名本身是一个指针的话，是不允许其出现在接收器中的**，比如下面这个例子：

```go
type	P	*int 
func	(P)	f()	{	/*	...	*/	}	//	compile	error:	invalid	receiver	type
```

1. 不管你的method的receiver是指针类型还是非指针类型，都是可以通过指针/非指针类型 进行调用的，编译器会帮你做类型转换。
2. 在声明一个method的receiver该是指针还是非指针类型时，你需要考虑两方面的内部，第 一方面是这个对象本身是不是特别大，如果声明为非指针变量时，调用会产生一次拷贝；第二方面是如果你用指针类型作为receiver，那么你一定要注意，这种指针类型指向 的始终是一块内存地址，就算你对其进行了拷贝。熟悉C或者C艹的人这里应该很快能明 白

### 使用嵌入类型扩展类型

使用嵌入结构体时，被嵌入结构体可以直接调用嵌入结构体的方法，

```go
import "image/color"
type Point struct{ X, Y float64 }
type ColoredPoint struct {
    Point
    Color color.RGBA
}

red := color.RGBA{255, 0, 0, 255}
blue := color.RGBA{0, 0, 255, 255}
var p = ColoredPoint{Point{1, 1}, red}
var q = ColoredPoint{Point{5, 4}, blue}
fmt.Println(p.Distance(q.Point)) // "5"   Distance是point类型的方法，p的类型为ColoredPoint，但可以直接调用Distance
p.ScaleBy(2)
q.ScaleBy(2)
fmt.Println(p.Distance(q.Point)) // "10" 但参数类型为Point时，必须显示调用point字段
```

### 方法值和方法表达式

可以将特定变量的方法调用赋值给变量，通过变量调用方法，其形式类似于函数变量的赋值：

```go
p := Point{1, 2}
q := Point{4, 6}
distanceFromP := p.Distance // method value，选择器返回一个方法值
fmt.Println(distanceFromP(q)) // "5"

scaleP := p.ScaleBy // method value，选择器返回一个方法值
scaleP(2) // p becomes (2, 4)

```

`p.distance`，`p.ScaleBy称为`选择器，选择器返回一个方法值。

在一个包的API需要一个函数值、且调用方希望操作的是某一个绑定了对象的方法的话，方
法"值"会非常实用。举例来说，下面例子中的`time.AfterFunc`这个函数的功能是在指定的延迟时间之后来执行一个(译注：另外的)函数。且这个函数操作的是一个Rocket对象r

```go
type Rocket struct { /* ... */ }
func (r Rocket) Launch() { / ... */ }
r := new(Rocket)
time.AfterFunc(10 * time.Second, func() { r.Launch() })      //这里相当于将r.Launch封装为一个函数传入
```

直接用方法"值"传入`AfterFunc`的话可以更为简短：

```go
time.AfterFunc(10 * time.Second, r.Launch)
```

和方法"值"相关的还有方法表达式。当调用一个方法时，与调用一个普通的函数相比，我们必须要用选择器(p.Distance)语法来指定方法的接收器。当T是一个类型时，方法表达式可能会写作T.f或者(*T).f，会返回一个函数"值"，这种函数会将
其第一个参数用作接收器，所以可以用通常(译注：不写选择器)的方式来对其进行调用：

```go
p := Point{1, 2}
q := Point{4, 6}
//这里Point是类型名，其拥有一个方法func (p Point) Distance()，
distance := Point.Distance // method expression 
fmt.Println(distance(p, q)) // "5"
fmt.Printf("%T\n", distance) // "func(Point, Point) float64"
scale := (*Point).ScaleBy
scale(&p, 2)
fmt.Println(p) // "{2 4}"
fmt.Printf("%T\n"
, scale) // "func(*Point, float64)"
```

以上的内容相当于将类型的一个方法转化为一个函数，该函数相较于方法多了第一个参数，该参数表明接收器，如上述将方法`func (p Point) Distance()float64 `转化为`func(Point, Point) float64`

## 接口

在Go语言中还存在着另外一种类型：接口类型。接口类型是一种抽象的类型。它不会暴露出它所代表的对象的内部值的结构和这个对象支持的基础操作的集合；它们只会展示出它们自己的方法。也就是说当你有看到一个接口类型的值时，你不知道它是什么，唯一知道的就是可以通过它的方法来做什么。

nil 接口值既不保存值也不保存具体类型。

也就是说，如果一个类型声明了某个接口给出的所有方法，则认为该类型继承了该接口，而无需显式说明。

### 常用内建接口

`Stringer` 是一个可以用字符串描述自己的类型。`fmt` 包（还有很多包）都通过此接口来打印值

```go
type Person struct {
	Name string
	Age  int
}

func (p Person) String() string {
	return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

func main() {
	a := Person{"Arthur Dent", 42}
	z := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(a, z)  //Arthur Dent (42 years) Zaphod Beeblebrox (9001 years)
}
```

### error接口

Go 程序使用 `error` 值来表示错误状态。与 `fmt.Stringer` 类似，`error` 类型是一个内建接口：

```go
type error interface {
    Error() string
}
```

（与 `fmt.Stringer` 类似，`fmt` 包在打印值时也会满足 `error`。）

### http.Handler接口

```go
package http
type Handler interface {
	ServeHTTP(w ResponseWriter, r *Request)
}
func ListenAndServe(address string, h Handler) error
```

ListenAndServe函数需要一个例如“localhost:8000”的服务器地址，和一个所有请求都可以分派的Handler接口实例。它会一直运行，直到这个服务因为一个错误而失败（或者启动失败），它的返回值一定是一个非空的错误。

### 类型断言

**类型断言** 提供了访问接口值底层具体值的方式。

```
t := i.(T)
```

该语句断言接口值 `i` 保存了具体类型 `T`，并将其底层类型为 `T` 的值赋予变量 `t`。若 `i` 并未保存 `T` 类型的值，该语句就会触发一个panic。

这里有两种可能。第一种，如果断言的类型T是一个具体类型，然后类型断言检查x的动态类型是否和T相同。如果这个检查成功了，类型断言的结果是x的动态值，当然它的类型是T。换句话说，具体类型的类型断言从它的操作对象中获得具体的值。如果检查失败，接下来这个操作会抛出panic。例如：

```go
var w io.Writer
w = os.Stdout
f := w.(*os.File) // success: f == os.Stdout
c := w.(*bytes.Buffer) // panic: interface holds *os.File, not *bytes.Buffer
```

上述中，w为`os.Stdout`，其类型为`*os.File`,所以`w.(*os.File)`断言成功，返回w的动态值，即`os.Stdout`。因为w的类型与`*bytes.Buffer`不符，所以`c :=w.(*bytes.Buffer)`运行时返回panic

如果断言类型T是接口类型，则类型断言检查x的动态类型是否满足T.如果此检查成功，在下面代码中，`w.(io.ReadWriter)`检查的是w的动态类型(即`os.Stdout`的动态类型`io.ReadWriter`)，与w的接口`io.Writer`无关。

```go
	var w io.Writer
	w = os.Stdout
	rw := w.(io.ReadWriter) // success: *os.File has both Read and Write
	w.Write([]byte("w write "))
	//	w.Read([]byte("w read"))   //w.Read undefined (type io.Writer has no field or method Read)
	rw.Read([]byte("rw read"))
	rw.Write([]byte("rw write"))
```

在上面的第一个类型断言后，w和rw都持有`os.Stdout`因此它们每个有一个动态类型`*os.File`，但是变量w是一个`io.Write`, r类型只对外公开出文件的Write方法，然而rw变量同时公开它的Read和write方法。

如果断言操作的对象是一个nil接口值，那么不论被断言的类型是什么这个类型断言都会失败。

为了 判断 一个接口值是否保存了一个特定的类型，类型断言可返回两个值：其底层值以及一个报告断言是否成功的布尔值。

```
t, ok := i.(T)
```

```go
func main() {
	var i interface{} = "hello"

	s := i.(string)           //i保存的值的具体类型为string
	fmt.Println(s)

	s, ok := i.(string)
	fmt.Println(s, ok)

	f, ok := i.(float64)
	fmt.Println(f, ok)

	f = i.(float64) // 报错(panic)
	fmt.Println(f)
}
```

### 类型选择

**类型选择** 是一种按顺序从几个类型断言中选择分支的结构。

类型选择与一般的 switch 语句相似，不过类型选择中的 case 为类型（而非值）， 它们针对给定接口值所存储的值的类型进行比较。

```go
func do(i interface{}) {
	switch v := i.(type) {
	case int:
		fmt.Printf("Twice %v is %v\n", v, v*2)
	case string:
		fmt.Printf("%q is %v bytes long\n", v, len(v))
	default:
		fmt.Printf("I don't know about type %T!\n", v)
	}
}

func main() {
	do(21)
	do("hello")
	do(true)
}
```

   ## 并发

### Goroutines

Go 程（goroutine）是由 Go 运行时管理的轻量级线程。

```
go f(x, y, z)
```

会启动一个新的 Go 程并执行

### Channels

信道是带有类型的管道，你可以通过它用信道操作符 `<-` 来发送或者接收值。

```go
ch <- v    // 将 v 发送至信道 ch。
v := <-ch  // 从 ch 接收值并赋予 v。
```

（“箭头”就是数据流的方向。）

和映射与切片一样，信道在使用前必须创建：

```go
ch := make(chan int)
ch := make(chan int, 100)       //带缓冲信道
```

默认情况下，发送和接收操作在另一端准备好之前都会**阻塞**。这使得 Go 程可以在没有显式的锁或竞态变量的情况下进行同步。	 	

#### 关闭信道

发送者可通过 `close(ch)` 关闭一个信道来表示没有需要发送的值了。接收者可以通过为接收表达式分配第二个参数来测试信道是否被关闭：若没有值可以接收且信道已被关闭，那么在执行完

```go
v, ok := <-ch
```

之后 `ok` 会被设置为 `false`值。循环 `for i := range c` 会不断从信道接收值，直到它被关闭。

*注意：* **只有发送者才能关闭信道，而接收者不能。**向一个已经关闭的信道发送数据会引发程序恐慌（panic）。

当一个被关闭的channel中已经发送的数据都被成功接收后，后续的接收操作将不再阻塞，它们会立即返回一个零

*还要注意：* 信道与文件不同，通常情况下无需关闭它们。只有在必须告诉接收者不再有需要发送的值时才有必要关闭，例如终止一个 `range` 循环。

#### 单向channel

Go语言的类型系统提供了单方向的channel类型，分别用于只发送或只接收的`channel`。类型 `chan<- int `表示一个只发送int的channel，只能发送不能接收。相反，类型` <-chan int` 表示一个只接收int的channel，只能接收不能发送。（箭头 <- 和关键字chan的相对位置表明了channel的方向。）这种限制将在编译期检测。

#### 带缓存的channel

带缓存的Channel内部持有一个元素队列。队列的最大容量是在调用make函数创建channel时通过第二个参数指定的。下面的语句创建了一个可以持有三个字符串元素的带缓存Channel。

```go
ch = make(chan string, 3)
```

使用内置函数cap可以获取channel缓存大小, 函数len可以获取channel有效数据个数

```go
fmt.Println(cap(ch))     //缓冲区大小
fmt.Println(len(ch))     //channel中的有效数据个数
```

- [ ] `make(chan int)`和`make(chan int,1)`的区别
### select

`select` 语句使一个 Go 程可以等待多个通信操作。

`select` 会阻塞到某个分支可以继续执行为止，这时就会执行该分支。**当多个分支都准备好时会随机选择一个执行。**

当 `select` 中的其它分支都没有准备好时，`default` 分支就会执行。为了在尝试发送或者接收时不发生阻塞，可使用 `default` 分支：

```go
select {
case i := <-c:
    // 使用 i
default:
    // 从 c 中接收会阻塞时执行
}
```

### Goroutines和线程

### 栈

每一个OS线程都有一个固定大小的内存块(一般会是2MB)来做栈，这个栈会用来存储当前正在被调用或挂起(指在调用其它函数时)的函数的内部变量。

相反，一个goroutine会以一个很小的栈开始其生命周期，一般只需要2KB。一个goroutine的栈，和操作系统线程一样，会保存其活跃或挂起的函数调用的本地变量，但是和OS线程不太一样的是一个goroutine的栈大小并不是固定的；栈的大小会根据需要动态地伸缩。

### 调度

OS线程由操作系统内核调用调用时会产生上下文切换，消耗资源较多

GO自身包含调度器，其调度消耗小于线程切换

### Goroutine没有ID号

在大多数支持多线程的操作系统和程序语言中，当前的线程都有一个独特的身份(id)，并且这个身份信息可以以一个普通值的形式被被很容易地获取到，典型的可以是一个integer或者指针值。goroutine没有可以被程序员获取到的身份(id)的概念。


