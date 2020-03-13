-- written in Haskell
import Data.Complex
import Graphics.Gnuplot.Simple

myPlot::String->Double->[(Double, Double)]->IO()
myPlot title ratio points = plotPathStyle attribute style points
  where
    attribute = [
      Title "",
      XLabel "x",
      YLabel "y",
      Aspect (Ratio ratio),
      EPS (if title == "" then "graph.eps" else (title++".eps")),
      Custom "terminal" ["eps","enhanced","color"]
      ]
    style = defaultStyle {lineSpec = CustomStyle [
      LineTitle "",
      LineWidth 2.0
      ]}
type Comp = Complex Double
eEuler::(Comp, Comp)->Int->[(Double, Double)]
eEuler _ 0 = []
eEuler (y1',y2') n = (py1,py2):(eEuler (y1,y2) (n-1))
  where
    y1 = y1' * (1:+h)
    y2 = y2' * (1:+(-h))
    py1 = realPart ((0:+1) * y1 + y2)
    py2 = realPart (y1 + (0:+1) * y2)
iEuler::(Comp, Comp)->Int->[(Double, Double)]
iEuler _ 0 = []
iEuler (y1',y2') n = (py1,py2):(iEuler (y1,y2) (n-1))
  where
    y1 = y1' / (1:+(-h))
    y2 = y2' / (1:+h)
    py1 = realPart ((0:+1) * y1 + y2)
    py2 = realPart (y1 + (0:+1) * y2)
trapezoidal::(Comp, Comp)->Int->[(Double, Double)]
trapezoidal _ 0 = []
trapezoidal (y1',y2') n = (py1,py2):(trapezoidal (y1,y2) (n-1))
  where
    y1 = y1' * (1:+0.5*h) / (1:+(-0.5*h))
    y2 = y2' * (1:+(-0.5*h)) / (1:+0.5*h)
    py1 = realPart ((0:+1) * y1 + y2)
    py2 = realPart (y1 + (0:+1) * y2)
rungeKutta::(Comp, Comp)->Int->[(Double, Double)]
rungeKutta _ 0 = []
rungeKutta (y1',y2') n = (py1,py2):(rungeKutta (y1,y2) (n-1))
  where
    y1 = y1' * ((1 - h^2/2 + h^4/24) :+ (h - h^3/6))
    y2 = y2' * ((1 - h^2/2 + h^4/24) :+ (-h + h^3/6))
    py1 = realPart ((0:+1) * y1 + y2)
    py2 = realPart (y1 + (0:+1) * y2)
h::Double
h = 0.05
n::Int
n = 20000
main::IO()
main = myPlot "eEuler" 1 points
  where
    points = eEuler (0:+(-0.5), 0.5) n
