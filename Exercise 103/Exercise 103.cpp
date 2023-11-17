Public Class Form1
    Private Sub Button1_Click() Handles Button1.Click
        Dim sw As New Stopwatch
        sw.Start()
        Dim result As String
        Dim total As Integer = 10 ^ 6
        Dim stuff As List(Of Integer)
        For a As Integer = 15 To 44
            For b As Integer = a + 1 To 45
                For c As Integer = b + 1 To 46
                    For d As Integer = c + 1 To 47
                        For e As Integer = d + 1 To 48
                            For f As Integer = e + 1 To 49
                                For g As Integer = f + 1 To Math.Min(Math.Min(Math.Min(a + b - 1, a + b + c - f - 1), a + b + c + d - f - e - 1), total - a - b - c - d - e - f - 1)
                                    stuff = New List(Of Integer)
                                    stuff.Add(a)
                                    stuff.Add(b)
                                    stuff.Add(c)
                                    stuff.Add(d)
                                    stuff.Add(e)
                                    stuff.Add(f)
                                    stuff.Add(g)
                                    If special(stuff) Then
                                        total = a + b + c + d + e + f + g
                                        result = CStr(a) & CStr(b) & CStr(c) & CStr(d) & CStr(e) & CStr(f) & CStr(g)
                                    End If
                                Next
                            Next
                        Next
                    Next
                Next
            Next
        Next
        TextBox1.Text = result
        textbox2.text = CStr(sw.ElapsedMilliseconds) & " ms"
    End Sub
    Private Function special(ByVal input As List(Of Integer)) As Boolean
        Dim curr As String
        Dim now As Integer
        Dim sums As New List(Of Integer)
        For i As Integer = 0 To 127
            curr = tenToTwo(i)
            now = 0
            For j As Integer = 0 To 6
                now += input(j) * CInt(curr.Substring(j, 1))
            Next
            If sums.Contains(now) Then Return False Else sums.Add(now)
        Next
        Return True
    End Function
    Private Function tenToTwo(ByVal input As Integer) As String
        Dim output As String = ""
        For i As Integer = 6 To 0 Step -1
            If input >= 2 ^ i Then
                input -= 2 ^ i
                output &= "1"
            Else : output &= "0"
            End If
        Next
        Return output
    End Function
End Class