import smtplib
from email.mime.text import MIMEText

def send_email(otp, recipient_email):
    sender_email = "sender@gmail.com"
    sender_password = "password_app"

    # Create the email content
    subject = "Your OTP Code"
    body = f"Your One-Time Password (OTP) is: {otp}"
    msg = MIMEText(body)
    msg['Subject'] = subject
    msg['From'] = sender_email
    msg['To'] = recipient_email

    # Send the email using Gmail's SMTP server
    try:
        with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:
            server.login(sender_email, sender_password)
            server.sendmail(sender_email, recipient_email, msg.as_string())
            print(f"OTP {otp} sent to {recipient_email}")
    except Exception as e:
        print(f"Error sending email: {e}")

if __name__ == "__main__":
    import sys
    otp = sys.argv[1]
    recipient_email = sys.argv[2]
    send_email(otp, recipient_email)

