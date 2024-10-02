#include "cart.h"



Cart::Cart()
{
    Initialize_Data_Base(Get_Data_Base_Name());
}
void Cart::AddItem(int Product_ID,int Quantity)
{
    QString quantity=Return_Item("Products","Stock_Quantity",QString("WHERE Product_Id = %1").arg(Product_ID));
    if(quantity == "No")
    {
        QMessageBox::critical(this,"Critical","there is no product with this id");
        return;
    }
    else if (Quantity > quantity.toInt())
    {
        QMessageBox::critical(this,"Critical","there is no enough quantity");
        return;

    }
    else
    {
        bool flag{false};

        QString Product_Id = Return_Item("Products","Product_Id",QString("WHERE Product_Id = %1").arg(Product_ID));
        QString Product_Name = Return_Item("Products","Name",QString("WHERE Product_Id = %1").arg(Product_ID));
        QString Product_Price = Return_Item("Products","Price",QString("WHERE Product_Id = %1").arg(Product_ID));
        QString Product_Category = Return_Item("Products","Category",QString("WHERE Product_Id = %1").arg(Product_ID));


        QString sql;
        QString my_Quantity = Return_Item("Cart_Products","Quantity",QString("WHERE Product_Id = %1").arg(Product_ID));
        if(my_Quantity == "No")
        {
            // not found in my products
            sql = QString("INSERT INTO Cart_Products (Product_Id, Name, Price,Total_Price, Quantity, Category) VALUES (%1, '%2', %3, %4, %5, '%6')")
            .arg(Product_Id.toInt())
                .arg(Product_Name)
                .arg(Product_Price.toFloat())
                .arg(Product_Price.toFloat() * Quantity)
                .arg(Quantity)
                .arg(Product_Category);
            if(insertData(sql))
            {
                flag = true;
            }
            else
            {
                flag = false;
            }
        }
        else
        {
            // update with the new quantity

            sql = QString("UPDATE Cart_Products SET Total_Price = %1, Quantity=%2")
                      .arg(Product_Price.toFloat() * (Quantity + my_Quantity.toInt()))
                      .arg(Quantity + my_Quantity.toInt());

            if(updateData(sql))
            {
                flag = true;

            }
            else
            {
                flag = false;
            }
        }


        if(flag)
        {
            QString sql;
            int newStock_Quantity = quantity.toInt() -  Quantity;
            sql = QString("UPDATE Products SET Stock_Quantity = '%1' WHERE Product_Id = %2")
                      .arg(newStock_Quantity)
                      .arg(Product_Id.toInt());
            if(updateData(sql))
            {
                QMessageBox::information(this,"information","Successfully added to your cart");
            }
        }
        else
        {
            QMessageBox::critical(this,"Critical","something is wrong");

        }

    }

}
void Cart::RemoveItem(int Product_ID,int Quantity)
{
    bool flag{false};
    QString sql;
    QString Shop_quantity=Return_Item("Products","Stock_Quantity",QString("WHERE Product_Id = %1").arg(Product_ID));
    QString my_cart_quantity=Return_Item("Cart_Products","Quantity",QString("WHERE Product_Id = %1").arg(Product_ID));
    QString Product_Price = Return_Item("Cart_Products","Price",QString("WHERE Product_Id = %1").arg(Product_ID));

    if(my_cart_quantity == "No")
    {
        QMessageBox::critical(this,"Critical","there is no product with this id in your cart");
        return;
    }
    else if (Quantity > my_cart_quantity.toInt())
    {
        QMessageBox::critical(this,"Critical","You haven't this quantity into your cart");
        return;

    }
    else
    {
        if(Quantity == my_cart_quantity.toInt())
        {
            // delete this product from your cart
            sql = QString("DELETE FROM Cart_Products WHERE Product_Id = %1").arg(Product_ID);
            if(updateData(sql))
            {
                flag = true;
            }
        }
        else
        {
            // update with the new quantity
            sql = QString("UPDATE Cart_Products SET Total_Price = %1, Quantity=%2")
                      .arg(Product_Price.toFloat() * (my_cart_quantity.toInt() - Quantity))
                      .arg(my_cart_quantity.toInt() -Quantity);
            if(updateData(sql))
            {
                flag = true;
            }
            else
            {
                flag = false;
            }
        }




        if(flag)
        {
            // add this quantity to the product table
            sql = QString("UPDATE Products SET Stock_Quantity = %1 WHERE Product_Id = %2")
                      .arg(Shop_quantity.toInt() + Quantity)
                      .arg(Product_ID);
            if(updateData(sql))
            {
                QMessageBox::information(this,"information","Successfully deleted from your cart");
            }
            qDebug() << "update ............"
                     <<(Shop_quantity.toInt() + Quantity);

        }
        else
        {
            QMessageBox::critical(this,"Critical","something is wrong");

        }

    }
}
void Cart::UpdateQuantity()
{

}
float Cart::CalculateTotal(void)
{
    float totalPrice;
    QString sumQuery = "SELECT SUM(Total_Price) AS TotalPrice FROM Cart_Products";
    if(query->exec(sumQuery)) {
        if(query->next()) {
            totalPrice = query->value(0).toDouble();
            qDebug() << "Total Price:" << totalPrice;
        }
    } else {
        qDebug() << "Query execution failed:" << query->lastError();
    }

    return totalPrice;
}

float Cart::apply_discount(float total_amount)
{
    float discount,final;
    if(total_amount < 1000)
    {
        discount = 0.0;
    }
    else if((total_amount > 1000) && (total_amount <= 1500))
    {
        discount = 0.5;
    }
    else if((total_amount > 1500) && (total_amount <= 2000))
    {
        discount = 1.0;
    }
    else if((total_amount > 2000) && (total_amount <= 2500))
    {
        discount = 1.5;
    }
    else if(total_amount > 2500)
    {
        discount = 2.0;
    }

    final = (total_amount) - ((total_amount * discount)/100);
    return final;
}

