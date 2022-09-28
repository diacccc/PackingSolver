# PackingSolver

```
foreach($file in get-childitem CLASS/cl_01_***_**.ins2D)
{
./main CLASS/($file.name)
}
```

```
foreach($file in get-childitem CLASS/cl_01_***_**.ins2D)
{
$x = "CLASS/"
$x = $x + $file.Name
./main $x
}
```
