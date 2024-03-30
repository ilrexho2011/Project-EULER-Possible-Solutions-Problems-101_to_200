Structure la
        Public num As Long
        Public h() As Byte
    End Structure
    Dim num As Integer = 9
    Dim lar As Integer = 12
    Dim m(lar, 3 ^ num - 1) As la
    Sub Main()
        Dim t As la
        Dim i As Long, j As Long, k As Long, l As Long, a As Integer
        For i = 0 To lar
            For j = 0 To 3 ^ num - 1
                ReDim m(i, j).h(num)
            Next
        Next
        ReDim t.h(num)
        t.num = 1
        For i = 1 To num
            t.h(i) = 1
        Next
        f1(1, t, 1)
        For i = 2 To lar
            For j = 0 To 3 ^ num - 1
                If m(i - 1, j).num > 0 Then
                    t.num = m(i - 1, j).num
                    k = 0
                    a = 0
                    If i <= 2 Then a = 1
                    For l = 1 To num
                        t.h(l) = (m(i - 1, j).h(l) + 1) Mod 3
                        k += t.h(l) * 3 ^ (l - 1)
                        If m(i - 1, j).h(l) = 0 Then a = 1
                    Next
                    If a = 1 Then
                        f1(i, t, 1)
                    End If
                End If
            Next
            For j = 0 To 3 ^ num - 1
                If m(i - 2, j).num > 0 Then
                    t.num = m(i - 2, j).num
                    a = 0
                    For l = 1 To num
                        If m(i - 2, j).h(l) = 2 Then GoTo a
                        t.h(l) = (m(i - 2, j).h(l) + 2) Mod 3
                        If m(i - 2, j).h(l) = 0 Then a = 1
                    Next
                    If a = 1 Then
                        f1(i, t, 1)
                    End If
                End If
a:
            Next
            If i > 3 Then m(i, 0).num += m(i - 3, 0).num
            If i = 3 Then m(3, 0).num += 1
            Debug.Print(m(i, 0).num)
        Next
        MsgBox(m(lar, 0).num)
    End Sub
    Sub f1(ByVal l As Integer, ByVal t As la, ByVal st As Integer)
        Dim i As Long, j As Long, k As Long, n As Integer, s As la
        ReDim s.h(num)
        j = 0
        For i = 0 To num - 1
            j += t.h(i + 1) * 3 ^ i
        Next
        m(l, j).num += t.num
        For i = 1 To num
            m(l, j).h(i) = t.h(i)
            If t.h(i) = 2 Then k = 1
            If t.h(i) = 1 Then n = 1
        Next
        If k = 1 Then
            For i = st To num - 1
                If t.h(i) = 2 And t.h(i + 1) = 1 Then
                    s.num = t.num
                    For j = 1 To num
                        s.h(j) = t.h(j)
                    Next
                    s.h(i) = 0
                    s.h(i + 1) = 0
                    f1(l, s, i + 2)
                End If
            Next
            For i = st To num - 1
                If t.h(i) = 1 And t.h(i + 1) = 2 Then
                    s.num = t.num
                    For j = 1 To num
                        s.h(j) = t.h(j)
                    Next
                    s.h(i) = 0
                    s.h(i + 1) = 0
                    f1(l, s, i + 2)
                End If
            Next
            For i = st To num - 1
                If t.h(i) = 2 And t.h(i + 1) = 2 Then
                    s.num = t.num
                    For j = 1 To num
                        s.h(j) = t.h(j)
                    Next
                    s.h(i) = 1
                    s.h(i + 1) = 0
                    f1(l, s, i + 2)
                    s.h(i) = 0
                    s.h(i + 1) = 1
                    f1(l, s, i + 1)
                End If
            Next
            For i = st To num - 1
                If i <= num - 2 Then
                    If t.h(i) = 2 And t.h(i + 1) = 2 And t.h(i + 2) = 2 Then
                        s.num = t.num
                        For j = 1 To num
                            s.h(j) = t.h(j)
                        Next
                        s.h(i) = 0
                        s.h(i + 1) = 0
                        s.h(i + 2) = 0
                        f1(l, s, i + 3)
                    End If
                End If
            Next
            For i = st To num - 3
                If t.h(i) = 1 And t.h(i + 1) = 1 And t.h(i + 2) = 2 And t.h(i + 3) = 2 Then
                    s.num = t.num
                    For j = 1 To num
                        s.h(j) = t.h(j)
                    Next
                    s.h(i) = 0
                    s.h(i + 1) = 0
                    s.h(i + 2) = 0
                    s.h(i + 3) = 0
                    f1(l, s, i + 4)
                End If
            Next
        End If
        If n = 1 Then
            For i = st To num - 2
                If t.h(i) = 1 And t.h(i + 1) = 1 And t.h(i + 2) = 1 Then
                    s.num = t.num
                    For j = 1 To num
                        s.h(j) = t.h(j)
                    Next
                    s.h(i) = 0
                    s.h(i + 1) = 0
                    s.h(i + 2) = 0
                    f1(l, s, i + 3)
                End If
            Next
        End If
    End Sub