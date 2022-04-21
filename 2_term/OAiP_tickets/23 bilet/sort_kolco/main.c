// Сортировка однонаправленного кольца
// изменением указателей

typedef struct ring
{
    int info;
    struct ring *next;
}ring;

void sort(ring **enter)
{
    ring *tempEnter, *prevTempEnter, *minElement, *prevElementToCompare, *elementToCompare, *prevMinElement;

    prevTempEnter = tempEnter = *enter;

    while(prevTempEnter->next != *enter)
        prevTempEnter = prevTempEnter->next;

    do
    {
        elementToCompare = tempEnter->next;
        prevElementToCompare = tempEnter;
        minElement = tempEnter;

        // Поиск минимального элемента в оставшемся списке
        do
        {
            if(minElement->info > elementToCompare->info)
            {
                minElement = elementToCompare;
                prevMinElement = prevElementToCompare;
            }
            elementToCompare = elementToCompare->next;
            prevElementToCompare = prevTempEnter->next;
        }while(elementToCompare->next != *enter);

        // Если найдено новое минимальное значение, то делаем замена
        if(minElement != tempEnter)
        {
            if(*enter == tempEnter)
                *enter = minElement;
            prevTempEnter->next = minElement;
            prevMinElement->next = minElement->next;
            minElement->next = tempEnter;
            prevTempEnter = minElement;
        }
        // В противном случае двигаемся дальше по кольцу
        else
        {
            tempEnter = tempEnter->next;
            prevTempEnter = prevTempEnter->next;
        }
    }while(tempEnter->next != *enter);
}