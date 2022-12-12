import scala.io.Source

object dec2 extends App {
  val filename = "C:/Users/Joachim/IdeaProjects/Golf/src/input.txt"
  val surs = Source.fromFile(filename)

  var score = 0

  val shapeScore = Map('A'->1, 'B'->2, 'C'->3)
  val beats = Map('A'->'C', 'B'->'A', 'C'->'B')
  val loses = Map('A'->'B', 'B'->'C', 'C'->'A')

  for (line <- surs.getLines) {
    score += ((line(0), line(2)) match{
      case ('A', 'X') => shapeScore(beats('A'))
      case ('B', 'X') => shapeScore(beats('B'))
      case ('C', 'X') => shapeScore(beats('C'))
      case ('A', 'Y') => shapeScore('A') + 3
      case ('B', 'Y') => shapeScore('B') + 3
      case ('C', 'Y') => shapeScore('C') + 3
      case ('A', 'Z') => shapeScore(loses('A')) + 6
      case ('B', 'Z') => shapeScore(loses('B')) + 6
      case ('C', 'Z') => shapeScore(loses('C')) + 6
      case _ => 0
    })
  }

  println(score)
}